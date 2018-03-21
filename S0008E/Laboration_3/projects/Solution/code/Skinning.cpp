#include "Skinning.h"
#include <fcntl.h>
#include <zconf.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <config.h>
#include <cstring>
#include "DDS_Types.h"

#define FOURCC_DXT1 'DXT1'

#if !defined(MAKEFOURCC)
#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
    (uint(uint8(ch0)) | (uint(uint8(ch1)) << 8) | \
    (uint(uint8(ch2)) << 16) | (uint(uint8(ch3)) << 24 ))
#endif


Skinning::Skinning()
{
}

Skinning::~Skinning()
{
    delete[] indiceBuffer;
    delete[] vertexBuffer;
    munmap(beginning, fileSize);
}

void Skinning::ReadHeadData(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    this->fileSize = st.st_size;

    int fd = open(filename,O_RDONLY);

    if(fd == -1)
    {
        perror("Could not open file!");
    }

    //Load file into memory
    void* ptr = mmap(NULL,  this->fileSize, PROT_READ, MAP_PRIVATE, fd,0);
    this->beginning  =  ptr;

    if(ptr == MAP_FAILED)
    {
        perror("Something is wrong!");
    }
    assert(0 != ptr);

    struct Nvx2Header* head = (struct Nvx2Header*) ptr;
    //Check if the magic is the same type as NVX2
    if(head->magic != 'NVX2')
    {
        perror("WE GOT NOTHING MAN!");
    }

    this->numGroups = head->numGroups;
    this->numVertices = head->numVertices;
    this->vertexWidth = head->vertexWidth;
    this->numIndices = head->numIndices*3;
    this->numEdges = head->numEdges;
    this->vertexComponentMask = head->vertexComponentMask;

    this->groupDataSize = 6 * sizeof(unsigned int) * this->numGroups;
    this->vertexDataSize = this->numVertices * this->vertexWidth * sizeof(float);
    this->indexDataSize = this->numIndices * sizeof(int);

    this->groupDataPtr = head + 1;
    this->vertexDataPtr = ((unsigned char*)this->groupDataPtr) + this->groupDataSize;
    this->indexDataPtr = ((unsigned char*)this->vertexDataPtr) + this->vertexDataSize;

    ReadPrimitive();

    close(fd);
}

void Skinning::ReadPrimitive()
{
    assert(this->numGroups > 0);
    assert(0 != this->groupDataPtr);
    Nvx2Group* group = (Nvx2Group*) this->groupDataPtr;

    for(int i = 0; i < size_t(this->numGroups); i++)
    {
        PrimitiveGroup pg;
        pg.numVertices = group->numVertices;
        pg.baseIndex = group->firstTriangle * 3;
        pg.numIndices = group->numTriangles * 3;
        primitive.push_back(pg);
        group++;
    }
}

void Skinning::SetupVertex()
{
    for(int i = 0; i < N2NumVertexComponents; i++)
    {
        VertexComponent::SemanticName sn;
        VertexComponent::Format format;

        int index = 0;

        if(vertexComponentMask & (1<<i))
        {
            switch (1<<i)
            {
                case N2Coord: //In use
                    sn = VertexComponent::Position;
                    format = VertexComponent::Float3;
                    break;

                case N2Normal:
                    sn = VertexComponent::Normal;
                    format = VertexComponent::Float3;
                    break;

                case N2NormalB4N: //In use
                    sn = VertexComponent::Normal;
                    format = VertexComponent::Byte4N;
                    break;

                case N2Uv0: //In use
                    sn = VertexComponent::TexCoord1;
                    format = VertexComponent::Float2;
                    index = 0;
                    break;

                case N2Uv0S2:
                    sn = VertexComponent::TexCoord1;
                    format = VertexComponent::Short2;
                    index = 0;
                    break;

                case N2Uv1:
                    sn = VertexComponent::TexCoord2;
                    format = VertexComponent::Float2;
                    index = 1;
                    break;

                case N2Uv1S2:
                    sn = VertexComponent::TexCoord2;
                    format = VertexComponent::Short2;
                    index = 1;
                    break;

                case N2Color:
                    sn = VertexComponent::Color;
                    format = VertexComponent::Float4;
                    break;

                case N2ColorUB4N:
                    sn = VertexComponent::Color;
                    format = VertexComponent::UByte4N;
                    break;

                case N2Tangent:
                    sn = VertexComponent::Tangent;
                    format = VertexComponent::Float3;
                    break;

                case N2TangentB4N: //In use
                    sn = VertexComponent::Tangent;
                    format = VertexComponent::Byte4N;
                    break;

                case N2Binormal:
                    sn = VertexComponent::Binormal;
                    format = VertexComponent::Float3;
                    break;

                case N2BinormalB4N: //In use
                    sn = VertexComponent::Binormal;
                    format = VertexComponent::Byte4N;
                    break;

                case N2Weights:
                    sn = VertexComponent::SkinWeights;
                    format = VertexComponent::Float4;
                    break;

                case N2WeightsUB4N: //In use
                    sn = VertexComponent::SkinWeights;
                    format = VertexComponent::UByte4N;
                    break;

                case N2JIndices:
                    sn = VertexComponent::SkinJIndices;
                    format = VertexComponent::Float4;
                    break;

                case N2JIndicesUB4: //In use
                    sn = VertexComponent::SkinJIndices;
                    format = VertexComponent::UByte4;
                    break;

                default:
                    std::cout << "Invalid VertexComponent! Default used!"<< std::endl;
                    sn = VertexComponent::Position;
                    format = VertexComponent::Float3;
                    break;
            }
            this->vertexComponents.push_back(VertexComponent(sn, index, format));
        }
    }
}

void Skinning::SetupVertexBuffer()
{
    this->vertexBuffer = new SkinVertex[this->numVertices];
    this->originalVertexBuffer = new SkinVertex[this->numVertices];
    for(int i = 0; i < this->numVertices; i++)
    {
        SkinVertex vertex;
        for(int j = 0; j < this->vertexComponents.size(); j++)
        {
            float x = 0,y = 0,z = 0,w = 0;
            float mult;
            float dot;

            switch (this->vertexComponents[j].semName)
            {

                case VertexComponent::Position:
                    tempVertex* pos;
                    pos = (tempVertex*)vertexDataPtr;

                    vertex.pos = Vector4D(pos->x,pos->y,pos->z);
                    this->vertexDataPtr += sizeof(float)*3;
                    break;

                case VertexComponent::Normal:
                    char* normal;
                    normal = (char*)vertexDataPtr;
                    x = (float)normal[0];
                    y = (float)normal[1];
                    z = (float)normal[2];
                    w = (float)normal[3];
                    vertex.normal = Vector4D(x,y,z,w);
                    this->vertexDataPtr += 4;
                    break;

                case VertexComponent::TexCoord1:
                    tempVertex* uv;
                    uv = (tempVertex*)vertexDataPtr;
                    vertex.uv = Vector4D(uv->x, uv->y,0);
                    this->vertexDataPtr += sizeof(float)*2;
                    break;

                case VertexComponent::Tangent:
                    char* tan;
                    tan = (char*)vertexDataPtr;
                    x = (float)tan[0];
                    y = (float)tan[1];
                    z = (float)tan[2];
                    w = (float)tan[3];
                    vertex.tangent = Vector4D(x,y,z,w);
                    this->vertexDataPtr += sizeof(signed char)*4;
                    break;

                case VertexComponent::Binormal:
                    char* bi;
                    bi = (char*)vertexDataPtr;
                    x = (float)bi[0];
                    y = (float)bi[1];
                    z = (float)bi[2];
                    w = (float)bi[3];
                    vertex.biNormal = Vector4D(x,y,z,w);
                    this->vertexDataPtr += sizeof(signed char)*4;
                    break;

                case VertexComponent::SkinWeights:
                    unsigned char* skinW;
                    skinW = (unsigned char*)vertexDataPtr;
                    x = (float)skinW[0];
                    y = (float)skinW[1];
                    z = (float)skinW[2];
                    w = (float)skinW[3];

                    vertex.skinWeight = Vector4D(x,y,z,w);
                    vertex.skinWeight = vertex.skinWeight * (1.0f/(vertex.skinWeight.QuaternionDot(Vector4D(1.0f,1.0f,1.0f,1.0f))));
                    this->vertexDataPtr += sizeof(unsigned char)*4;
                    break;

                case VertexComponent::SkinJIndices:
                    unsigned char* skinI;
                    skinI = (unsigned char*)vertexDataPtr;
                    x = (float)skinI[0];
                    y = (float)skinI[1];
                    z = (float)skinI[2];
                    w = (float)skinI[3];
                    vertex.indice = Vector4D(x,y,z,w);
                    this->vertexDataPtr += sizeof(unsigned char)*4;
                    break;
            }
        }
        this->vertexBuffer[i] = vertex;
        this->originalVertexBuffer[i] = vertex;
    }
}

void Skinning::SetupIndiceBuffer()
{
    this->indiceBuffer = new int[this->numIndices];
    for(int i = 0; i < this->numIndices; i++)
    {
        int* val = (int*)this->indexDataPtr;
        this->indiceBuffer[i] = *val;
        this->indexDataPtr += sizeof(int);
    }
}

void Skinning::SetBuffers()
{
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, this->numVertices*sizeof(SkinVertex),this->vertexBuffer ,GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32)*this->numIndices, indiceBuffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skinning::DrawSkin(Skeleton* skeleton)
{
    SetBuffers();
    skeleton->ConvertJointsToArray();

    skeleton->shader->ModifyMatrix("rotation", (float*)skeleton->test.Transpose().matrix);
//    skeleton->shader->ModifyMatrix("normalMat", (float*)skeleton->test.matrix);


    GLint position = glGetUniformLocation(skeleton->shader->program, "skeleton");
    glUniformMatrix4fv(position, 21, GL_TRUE, (float*)skeleton->mat);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, NULL);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 4));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 8));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 12));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 16));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 20));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 24));

    glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_INT, NULL);
//    glDrawArrays(GL_TRIANGLES, 0, this->numIndices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

void Skinning::BindToSkeleton(Skeleton *skeleton)
{
    skeleton->ConvertJointsToArray();
    int arr[21] = {19, 18, 17, 0, 20, 15, 13, 1, 12, 9, 2, 10, 3, 11, 14, 16, 4, 5, 8, 6, 7};
    for(int i = 0; i < this->numVertices; i++)
    {
        Vector4D np;

        int first ,second, third, fourth;
        first = arr[(int)this->originalVertexBuffer[i].indice.coordinates[0]];
        second = arr[(int)this->originalVertexBuffer[i].indice.coordinates[1]];
        third = arr[(int)this->originalVertexBuffer[i].indice.coordinates[2]];
        fourth = arr[(int)this->originalVertexBuffer[i].indice.coordinates[3]];

        Matrix4D m1 = skeleton->bindPose[first].transformMatrix.Inverse()  * skeleton->tempJoints[first].transformMatrix;
        Matrix4D m2 = skeleton->bindPose[second].transformMatrix.Inverse() * skeleton->tempJoints[second].transformMatrix;
        Matrix4D m3 = skeleton->bindPose[third].transformMatrix.Inverse()  * skeleton->tempJoints[third].transformMatrix;
        Matrix4D m4 = skeleton->bindPose[fourth].transformMatrix.Inverse() * skeleton->tempJoints[fourth].transformMatrix;

        m1 = m1.Transpose() * *this->originalVertexBuffer[i].skinWeight[0];
        m2 = m2.Transpose() * *this->originalVertexBuffer[i].skinWeight[1];
        m3 = m3.Transpose() * *this->originalVertexBuffer[i].skinWeight[2];
        m4 = m4.Transpose() * *this->originalVertexBuffer[i].skinWeight[3];
        m1 = m1 + m2 + m3 + m4;

        np = m1 * this->originalVertexBuffer[i].pos;
        this->vertexBuffer[i].pos = np * 0.3f;
    }
    SetBuffers();
}

GLuint Skinning::LoadDDS(const char *filepath, Skeleton* skeleton, int textureType)
{
    struct stat st;
    stat(filepath, &st);
    this->fileSize = st.st_size;

    int fd = open(filepath,O_RDONLY);

    if(fd == -1)
    {
        perror("Could not open file!");
    }

    //Load file into memory
    void* ptr = mmap(NULL,  this->fileSize, PROT_READ, MAP_PRIVATE, fd,0);
    this->beginning  =  ptr;
    uint32* magic = (uint32*)ptr;
    ptr += sizeof(uint32);
    DDS_HEADER* head = (DDS_HEADER*)ptr;
    ptr += sizeof(DDS_HEADER);

    int width = head->dwWidth;
    int height = head->dwHeight;
    int mipMapCount = head->dwMipMapCount;

    int fourCC = head->ddspf.dwFourCC;
    DXT10Header* dx10Head = nullptr;
    unsigned int format;

    GLint textureResource;
    switch (fourCC)
    {
        case MAKEFOURCC('D','X','T','1'):
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case MAKEFOURCC('D','X','T','3'):
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case MAKEFOURCC('D','X','T','5'):
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;

            glActiveTexture(GL_TEXTURE1);
            glGenTextures(1, &normalID);
            glBindTexture(GL_TEXTURE_2D, normalID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            textureResource = glGetUniformLocation(skeleton->shader->program, "normalTex");
            glUniform1i(textureResource, 1);
            break;

        case MAKEFOURCC('D','X','1','0'):
            dx10Head = (DXT10Header*)ptr;
            ptr += sizeof(DXT10Header);
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;

            if(textureType == 0)
            {
                glActiveTexture(GL_TEXTURE0);
                glGenTextures(1, &diffuseID);
                glBindTexture(GL_TEXTURE_2D, diffuseID);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                textureResource = glGetUniformLocation(skeleton->shader->program, "diffuseTex");
                glUniform1i(textureResource, 0);

            }
            else
            {
                glActiveTexture(GL_TEXTURE1);
                glGenTextures(1, &specularID);
                glBindTexture(GL_TEXTURE_2D, specularID);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                textureResource = glGetUniformLocation(skeleton->shader->program, "specTex");
                glUniform1i(textureResource, 0);
            }
            break;
    }
    int offset = 0;
    glBindTexture(GL_TEXTURE_2D, textureResource);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,0 , size, ptr + offset);

        offset += size;
        width /= 2;
        height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if (width < 1) width = 1;
        if (height < 1) height = 1;
    }
}
