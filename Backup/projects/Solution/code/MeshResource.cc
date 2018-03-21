#pragma	once
#include "MeshResource.h"
#include "config.h"
#include <string.h>

MeshResource::MeshResource()
{
    model = Matrix4D();
}

MeshResource::~MeshResource()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1,&ebo);

//	delete[] this->verticeBuffer;
//	delete[] this->indiceBuffer;

	verticeBuffer = nullptr;
	indiceBuffer = nullptr;
}


/**
* Method to set the VBO
*/
void MeshResource::SetBO()
{

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->num* sizeof(Vertex), this->verticeBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32)*this->sizeOfBuffer, indiceBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void MeshResource::MakeCube(float width, float height, float depth)
{
//	MeshResource* mesh = new MeshResource();

	verticeBuffer = new Vertex[8];
	indiceBuffer = new int[36];

	Vertex topLeft(-width, +height, +depth);
	Vertex topRight(+width, +height, +depth);
	Vertex bottomLeft(-width, -height, +depth);
	Vertex bottomRight(+width, -height, +depth);

	Vertex backsideTopLeft(-width, +height, -depth);
	Vertex backsideTopRight(+width, +height, -depth);
	Vertex backsideBottomLeft(-width, -height, -depth);
	Vertex backsideBottomRight(+width, -height, -depth);

	topLeft.uv = { 1.0f, 0.0f, 0.0f , 1.0f };
	topRight.uv = { 0.0f, 1.0f, 0.0f, 1.0f };
	bottomLeft.uv = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomRight.uv = { 1.0f, 0.0f, 1.0f , 1.0f };

	backsideTopLeft.uv = { 1.0f , 0.0f, 0.0f, 1.0f };
	backsideTopRight.uv = { 0.0f , 1.0f, 0.0f, 1.0f };
	backsideBottomLeft.uv = { 0.0f , 0.0f, 1.0f, 1.0f };
	backsideBottomRight.uv = { 1.0f , 1.0f, 0.0f, 1.0f };

	Vector4D uv1_bl(0, 0, 0, 0);
	Vector4D uv2_tl(0, 1, 0, 1);
	Vector4D uv3_br(1, 0, 1, 0);
	Vector4D uv4_tr(1, 1, 1, 1);

	backsideTopLeft.uv = uv2_tl;
	backsideBottomRight.uv = uv3_br;
	backsideBottomLeft.uv = uv1_bl;
	backsideTopRight.uv = uv4_tr;

	topLeft.uv = uv2_tl;
	bottomRight.uv = uv3_br;
	bottomLeft.uv = uv1_bl;
	topRight.uv = uv4_tr;

	verticeBuffer[0] = backsideTopLeft;
	verticeBuffer[1] = backsideBottomRight;
	verticeBuffer[2] = backsideBottomLeft;
	verticeBuffer[3] = backsideTopRight;

	verticeBuffer[4] = topLeft;
	verticeBuffer[5] = bottomRight;
	verticeBuffer[6] = bottomLeft;
	verticeBuffer[7] = topRight;


	indiceBuffer[0] = 3;
	indiceBuffer[1] = 2;
	indiceBuffer[2] = 1;
	indiceBuffer[3] = 0;
	indiceBuffer[4] = 2;
	indiceBuffer[5] = 3;

	indiceBuffer[6] = 7;
	indiceBuffer[7] = 1;
	indiceBuffer[8] = 5;
	indiceBuffer[9] = 3;
	indiceBuffer[10] = 1;
	indiceBuffer[11] = 7;

	indiceBuffer[12] = 4;
	indiceBuffer[13] = 5;
	indiceBuffer[14] = 6;
	indiceBuffer[15] = 7;
	indiceBuffer[16] = 5;
	indiceBuffer[17] = 4;

	indiceBuffer[18] = 0;
	indiceBuffer[19] = 6;
	indiceBuffer[20] = 2;
	indiceBuffer[21] = 4;
	indiceBuffer[22] = 6;
	indiceBuffer[23] = 0;

	indiceBuffer[24] = 6;
	indiceBuffer[25] = 1;
	indiceBuffer[26] = 2;
	indiceBuffer[27] = 5;
	indiceBuffer[28] = 1;
	indiceBuffer[29] = 6;

	indiceBuffer[30] = 0;
	indiceBuffer[31] = 7;
	indiceBuffer[32] = 4;
	indiceBuffer[33] = 3;
	indiceBuffer[34] = 7;
	indiceBuffer[35] = 0;

	sizeOfBuffer = 36;
	SetBO();

}


void MeshResource::MakeCube()
{

    verticeBuffer = new Vertex[8];
	indiceBuffer = new int[36];

	Vertex topLeft(-0.25f, +0.25f, +0.25f);
	Vertex topRight(+0.25f, +0.25f, +0.25f);
	Vertex bottomLeft(-0.25f, -0.25f, +0.25f);
	Vertex bottomRight(+0.25f, -0.25f, +0.25f);

	Vertex backsideTopLeft(-0.25f, +0.25f, -0.25f);
	Vertex backsideTopRight(+0.25f, +0.25f, -0.25f);
	Vertex backsideBottomLeft(-0.25f, -0.25f, -0.25f);
	Vertex backsideBottomRight(+0.25f, -0.25f, -0.25f);


	this->box.min = backsideTopLeft.pos;
	this->box.max = bottomRight.pos;

	Vector4D uv1(0, 0, 0, 0);
	Vector4D uv2(0, 1, 0, 1);
	Vector4D uv3(1, 0, 1, 0);
	Vector4D uv4(1, 1, 1, 1);


	backsideTopLeft.uv = uv2;
	backsideBottomRight.uv = uv3;
	backsideBottomLeft.uv = uv4;
	backsideTopRight.uv = uv1;

	topLeft.uv = uv4;
	bottomRight.uv = uv1;
	bottomLeft.uv = uv2;
	topRight.uv = uv3;

	verticeBuffer[0] = backsideTopLeft;
	verticeBuffer[1] = backsideBottomRight;
	verticeBuffer[2] = backsideBottomLeft;
	verticeBuffer[3] = backsideTopRight;

	verticeBuffer[4] = topLeft;
	verticeBuffer[5] = bottomRight;
	verticeBuffer[6] = bottomLeft;
	verticeBuffer[7] = topRight;

	indiceBuffer[0] = 3;
	indiceBuffer[1] = 2;
	indiceBuffer[2] = 1;
	indiceBuffer[3] = 0;

	indiceBuffer[4] = 2;
	indiceBuffer[5] = 3;
	indiceBuffer[6] = 7;
	indiceBuffer[7] = 1;

	indiceBuffer[8] = 5;
	indiceBuffer[9] = 3;
	indiceBuffer[10] = 1;
	indiceBuffer[11] = 7;

	indiceBuffer[12] = 4;
	indiceBuffer[13] = 5;
	indiceBuffer[14] = 6;
	indiceBuffer[15] = 7;

	indiceBuffer[16] = 5;
	indiceBuffer[17] = 4;
	indiceBuffer[18] = 0;
	indiceBuffer[19] = 6;

	indiceBuffer[20] = 2;
	indiceBuffer[21] = 4;
	indiceBuffer[22] = 6;
	indiceBuffer[23] = 0;

	indiceBuffer[24] = 6;
	indiceBuffer[25] = 1;
	indiceBuffer[26] = 2;
	indiceBuffer[27] = 5;

	indiceBuffer[28] = 1;
	indiceBuffer[29] = 6;
	indiceBuffer[30] = 0;
	indiceBuffer[31] = 7;

	indiceBuffer[32] = 4;
	indiceBuffer[33] = 3;
	indiceBuffer[34] = 7;
	indiceBuffer[35] = 0;

	sizeOfBuffer = 36;
	SetBO();

}

void MeshResource::MakeQuad(float size, Vector4D pos)
{
//	this->plane.distance = depth;
	this->translation.Set_Position(pos);
	verticeBuffer = new Vertex[4];
	indiceBuffer = new int[6];
//	this->plane.quadWidth = size;


	Vertex topLeft(-size, size, 0);
	Vertex topRight(size, size, 0);
	Vertex bottomLeft(-size, -size, 0);
	Vertex bottomRight(size, -size, 0);

	box.min = topLeft.pos;
	box.max = bottomRight.pos;

	topLeft.uv = { 0.0f, 1.0f, 0.0f , 1.0f };
	topRight.uv = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomLeft.uv = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomRight.uv = { 0.0f, 1.0f, 0.0f , 1.0f };

	verticeBuffer[0] = topLeft;
	verticeBuffer[1] = topRight;
	verticeBuffer[2] = bottomLeft;
	verticeBuffer[3] = bottomRight;


	indiceBuffer[0] = 0;
	indiceBuffer[1] = 1;
	indiceBuffer[2] = 2;

	indiceBuffer[3] = 2;
	indiceBuffer[4] = 3;
	indiceBuffer[5] = 1;

	this->sizeOfBuffer = 6;
	this->SetBO();
}


void MeshResource::MakeQuad()
{

	verticeBuffer = new Vertex[4];
	indiceBuffer = new int[6];
//	plane.quadWidth = 0.25;

	Vertex topLeft(-0.25f, 0.25f, 0.0f);
	Vertex topRight(0.25f, 0.25f, 0.0f);
	Vertex bottomLeft(-0.25f, -0.25f, 0.0f);
	Vertex bottomRight(0.25f, -0.25f, 0.0f);


	topLeft.uv = { 0.0f, 1.0f, 0.0f , 1.0f };
	topRight.uv = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomLeft.uv = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomRight.uv = { 0.0f, 1.0f, 0.0f , 1.0f };


	verticeBuffer[0] = topLeft;
	verticeBuffer[1] = topRight;
	verticeBuffer[2] = bottomLeft;
	verticeBuffer[3] = bottomRight;


	indiceBuffer[0] = 0;
	indiceBuffer[1] = 1;
	indiceBuffer[2] = 2;

	indiceBuffer[3] = 2;
	indiceBuffer[4] = 3;
	indiceBuffer[5] = 1;

	this->sizeOfBuffer = 6;
	this->SetBO();
}


void MeshResource::Draw()
{
	if(wireframe)
	{
//        if(!once)
//        {
//            sizeOfBuffer = sizeOfBuffer - 9;
//			tempIndice = indiceBuffer;
//			indiceBuffer = tempIndice + 7;
//            SetBO();
//            once = true;
//        }

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    }
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 12, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 12, (GLvoid*)(sizeof(float32) * 4));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 12, (GLvoid*)(sizeof(float32) * 8));

	glDrawElements(GL_TRIANGLES, sizeOfBuffer, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void MeshResource::Load(const char* filename)
{
    int numberOfFaces = 0;
    int sizeOfIndice = 0;
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    int numVertex = 0;

    std::vector<Vector4D> temp_uvs;
    std::vector<Vector4D> temp_normals;
    std::vector<Vertex> temp_vertex;

    Vector4D minimum(0,0,0);
    Vector4D maximum(0,0,0);

    FILE * myfile = fopen(filename, "r");
    if (myfile == NULL)
    {
        int k;
        printf("Unable to open the file!\n");
        printf("Press any Enter to exit.....");
        std::cin >> k;
        exit(1);
    }
    while (true)
    {
        char lineHeader[128];
        int res = fscanf(myfile, "%s", lineHeader);
        if (res == EOF)
        {
            break; //We are at the end of file, therefore we break the loop
        }
        if (strcmp(lineHeader, "v") == 0)
        {
            float x, y, z;
            numVertex++;
            fscanf(myfile, "%f %f %f\n", &x, &y, &z);

            Vector4D vertex(x, y, z);
            vertex = vertex;

            Vertex vert;
            vert.pos = vertex;
            temp_vertex.push_back(vert);
        }

        else if (strcmp(lineHeader, "vt") == 0)
        {
            Vector4D uv;
            fscanf(myfile, "%f %f\n", &uv[0], &uv[1]);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            Vector4D normal;
            fscanf(myfile, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
            temp_normals.push_back(normal);
        }

        else if (strcmp(lineHeader, "f") == 0)
        {

            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(myfile, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

            if (matches == 9)
            {
				numberOfFaces++;

				temp_vertex[vertexIndex[0]-1].uv = temp_uvs[uvIndex[0]-1];
                temp_vertex[vertexIndex[1]-1].uv = temp_uvs[uvIndex[1]-1];
                temp_vertex[vertexIndex[2]-1].uv = temp_uvs[uvIndex[2]-1];

                temp_vertex[vertexIndex[0]-1].normal = temp_normals[normalIndex[0]-1];
                temp_vertex[vertexIndex[1]-1].normal = temp_normals[normalIndex[1]-1];
                temp_vertex[vertexIndex[2]-1].normal = temp_normals[normalIndex[2]-1];


                vertexIndices.push_back(vertexIndex[0]-1);
                vertexIndices.push_back(vertexIndex[1]-1);
                vertexIndices.push_back(vertexIndex[2]-1);

				Edge* A = new Edge();
                Edge* B = new Edge();
                Edge* C = new Edge();
				A->start = temp_vertex[vertexIndex[0]-1].pos;
				B->start = temp_vertex[vertexIndex[1]-1].pos;
				C->start = temp_vertex[vertexIndex[2]-1].pos;

				A->end = temp_vertex[vertexIndex[1]-1].pos;
				B->end = temp_vertex[vertexIndex[2]-1].pos;
				C->end = temp_vertex[vertexIndex[0]-1].pos;

                A->next = B;
                B->next = C;
                C->next = A;

                Face* face = new Face();
                face->edge = A;
                edges.push_back(A);
                edges.push_back(B);
                edges.push_back(C);

                faces.push_back(face);
                sizeOfIndice+=3;
            }
            else if (matches == 12)
            {
                numberOfFaces++;
				temp_vertex[vertexIndex[0]-1].uv = temp_uvs[uvIndex[0]-1];
				temp_vertex[vertexIndex[1]-1].uv = temp_uvs[uvIndex[1]-1];
				temp_vertex[vertexIndex[2]-1].uv = temp_uvs[uvIndex[2]-1];
				temp_vertex[vertexIndex[3]-1].uv = temp_uvs[uvIndex[3]-1];

				temp_vertex[vertexIndex[0]-1].normal = temp_normals[normalIndex[0]-1];
				temp_vertex[vertexIndex[1]-1].normal = temp_normals[normalIndex[1]-1];
				temp_vertex[vertexIndex[2]-1].normal = temp_normals[normalIndex[2]-1];
				temp_vertex[vertexIndex[3]-1].normal = temp_normals[normalIndex[3]-1];

				vertexIndices.push_back(vertexIndex[0]-1);
				vertexIndices.push_back(vertexIndex[1]-1);
				vertexIndices.push_back(vertexIndex[2]-1);

                vertexIndices.push_back(vertexIndex[1]-1);
                vertexIndices.push_back(vertexIndex[2]-1);
				vertexIndices.push_back(vertexIndex[3]-1);

                Edge* A = new Edge();
                Edge* B = new Edge();
                Edge* C = new Edge();
                Edge* D = new Edge();

                A->start = temp_vertex[vertexIndex[0]-1].pos;
                B->start = temp_vertex[vertexIndex[1]-1].pos;
                C->start = temp_vertex[vertexIndex[2]-1].pos;
                D->start = temp_vertex[vertexIndex[3]-1].pos;


                A->end = temp_vertex[vertexIndex[1]-1].pos;
                B->end = temp_vertex[vertexIndex[2]-1].pos;
                C->end = temp_vertex[vertexIndex[3]-1].pos;
                D->end = temp_vertex[vertexIndex[0]-1].pos;


                A->next = B;
                B->next = C;
                C->next = D;
                D->next = A;

                Face* face = new Face();
                face->edge = A;

                edges.push_back(A);
                edges.push_back(B);
                edges.push_back(C);
                edges.push_back(D);

                faces.push_back(face);


                sizeOfIndice += 4;
            }
            else
            {
                std::cout << "Cant load file with this parser";
                std::cout << matches << std::endl;
            }
        }
    }
    printf("%i\n",temp_vertex.size());
    printf("%i\n",vertexIndices.size());
    verticeBuffer = new Vertex[temp_vertex.size()];
    indiceBuffer = new int[vertexIndices.size()];

    for (int k = 0; k < temp_vertex.size(); k++)
    {
        verticeBuffer[k] = temp_vertex[k];

    }

    for(int p = 0; p < vertexIndices.size(); p++)
    {
        indiceBuffer[p] = vertexIndices[p];
    }

    sizeOfBuffer =  vertexIndices.size();

    for (int k = 0; k < temp_vertex.size(); k++)
    {
        if(verticeBuffer[k].pos[0] < minimum[0]){minimum[0] = verticeBuffer[k].pos[0];}
        else if(verticeBuffer[k].pos[0] > maximum[0]){maximum[0] = verticeBuffer[k].pos[0];}

        if(verticeBuffer[k].pos[1] < minimum[1]){minimum[1] = verticeBuffer[k].pos[1];}
        else if(verticeBuffer[k].pos[1] > maximum[1]){maximum[1] = verticeBuffer[k].pos[1];}

        if(verticeBuffer[k].pos[2] < minimum[2]){minimum[2] = verticeBuffer[k].pos[2];}
        else if(verticeBuffer[k].pos[2] > maximum[2]){maximum[2] = verticeBuffer[k].pos[2];}

        this->verticeBuffer[k] = verticeBuffer[k];
    }

    this->box.max = maximum;
    this->box.min = minimum;
    
    num = temp_vertex.size();

    box.temp[0] = Vector4D(this->box.min[0],this->box.min[1],this->box.min[2]);
    box.temp[1] = Vector4D(this->box.min[0],this->box.max[1],this->box.min[2]);
    box.temp[2] = Vector4D(this->box.max[0],this->box.max[1],this->box.min[2]);
    box.temp[3] = Vector4D(this->box.max[0],this->box.min[1],this->box.min[2]);

    box.temp[4] = Vector4D(this->box.min[0],this->box.min[1],this->box.max[2]);
    box.temp[5] = Vector4D(this->box.min[0],this->box.max[1],this->box.max[2]);
    box.temp[6] = Vector4D(this->box.max[0],this->box.max[1],this->box.max[2]);
    box.temp[7] = Vector4D(this->box.max[0],this->box.min[1],this->box.max[2]);

    vertexIndices.clear();
    temp_vertex.clear();
    SetBO();
}

void MeshResource::DrawBorders()
{
	glBegin(GL_LINES);
	glColor3i(0,0,1);

	//Rendering the backside of the box
	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Top-Left Corner
	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Top-Right Corner

	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Top-Right Corner
	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Bottom-Right Corner

	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Bottom-Right Corner
	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Bottom-Left Corner

	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Bottom-Left Corner
	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Top-Left Corner

	//	Rendering the front of the box
	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Top-Left Corner
	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Top-Right Corner

	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Top-Right Corner
	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Bottom-Right Corner

	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Bottom-Right Corner
	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Bottom-Left Corner

	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Bottom-Left Corner
	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Top-Left Corner

	//The left sid.of the box
	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Back Top-Left Corner
	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Front Top-Left Corner

	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Front Top-Left Corner
	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Front Bottom-Left Corner

	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Front Bottom-Left Corner
	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Back Bottom-Left Corner

	glVertex3f(box.min[0]-0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Bottom-Left Corner
	glVertex3f(box.min[0]-0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Back Top-Left Corner

	//The right side of the box
	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Back Top-Left Corner
	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Front Top-Left Corner

	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.max[2]+0.01f);//<< Front Top-Left Corner
	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Front Bottom-Left Corner

	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.max[2]+0.01f);//<< Front Bottom-Left Corner
	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Back Bottom-Left Corner

	glVertex3f(box.max[0]+0.01f,box.max[1]-0.01f,box.min[2]-0.01f);//<< Bottom-Left Corner
	glVertex3f(box.max[0]+0.01f,box.min[1]+0.01f,box.min[2]-0.01f);//<< Back Top-Left Corner

	glEnd();
}

void MeshResource::SetPosition(Vector4D pos)
{
    this->translation.Set_Position(pos);

}

void MeshResource::SetBoxPosition(Vector4D pos)
{
    this->box.min = this->box.min + pos;
    this->box.max = this->box.max + pos;
}

void MeshResource::ReturnBoxPosition()
{
    this->box.min = this->tempMin;
    this->box.max = this->tempMax;
}

void MeshResource::CalculateAABB()
{

    Vector4D tempMin(100,100,100);
    Vector4D tempMax(-100,-100,-100);
    Vector4D temp;

    for(int i = 0; i < 8; i++)
    {
        temp = model * box.temp[i];

        if(temp[0]<tempMin[0]){ tempMin[0] = temp[0];}
        if(temp[1]<tempMin[1]){ tempMin[1] = temp[1];}
        if(temp[2]<tempMin[2]){ tempMin[2] = temp[2];}

        if(temp[0]>tempMax[0]){ tempMax[0] = temp[0];}
        if(temp[1]>tempMax[1]){ tempMax[1] = temp[1];}
        if(temp[2]>tempMax[2]){ tempMax[2] = temp[2];}

    }
    this->box.min = tempMin;
    this->box.max = tempMax;

}

void MeshResource::CalculateModelMatrix()
{
    this->model = this->translation * this->rotation * this->scale;

}


void MeshResource::Momentum()
{

}

Vector4D MeshResource::GetFarthestPointInDirection(Vector4D dir)
{
    float maxDot = -INFINITY;
    float tempDot = 0;
    Vector4D temp;
    Vector4D point;
    for(int i = 0; i < this->numVertices; i++)
    {
//        temp = (this->model * this->verticeBuffer[i].pos);
        temp = (this->model * this->box.temp[i]);

        tempDot = temp * dir;
        if(tempDot > maxDot)
        {
            maxDot = tempDot;
            point = temp;
        }
    }
    return point;
}