#include "HE_Mesh.h"
#include <map>
#include <string.h>
#include "config.h"

HE_Mesh::HE_Mesh()
{

}

HE_Mesh::~HE_Mesh()
{
    delete[] this->half_faces;
    delete[] this->half_edges;
    delete[] this->half_vertex;
    delete[] this->indiceBuffer;
}

HE_Mesh* HE_Mesh::LoadFromFile(const char *filename)
{
    HE_Mesh* hem = new HE_Mesh();
    int sizeOfIndice = 0;
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

//    std::vector<Vector4D>temp_vertices;
    std::vector<Vector4D> temp_uvs;
    std::vector<Vector4D> temp_normals;

    std::vector<HE_Vertex*> temp_vertex;

    std::vector<HE_Edge*> edges;
    std::vector<HE_Face*> faces;


    int fid = 0, eid = 1;
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
            hem->numVertex++;
            fscanf(myfile, "%f %f %f\n", &x, &y, &z);

            Vector4D vertex(x, y, z);
            vertex = vertex*0.75f;

            HE_Vertex* vert = new HE_Vertex();
            vert->pos = vertex;
            temp_vertex.push_back(vert);
//            temp_vertices.push_back(vertex);
        }

        else if (strcmp(lineHeader, "vt") == 0)
        {
            Vector4D uv;
            fscanf(myfile, "%f %f\n", uv[0], uv[1]);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            Vector4D normal;
            fscanf(myfile, "%f %f %f\n", normal[0], normal[1], normal[2]);
            temp_normals.push_back(normal);
        }

        else if (strcmp(lineHeader, "f") == 0)
        {
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(myfile, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

            if (matches == 9)
            {
//                hem->renderingMode = GL_TRIANGLES;
//                HE_Edge A;
//                HE_Edge B;
//                HE_Edge C;
//
//                hem->numEdges += 3;
//
//                temp_vertex[vertexIndex[0]-1]->edge = &A;
//                temp_vertex[vertexIndex[1]-1]->edge = &B;
//                temp_vertex[vertexIndex[2]-1]->edge = &C;
//
//                hem->numVertex += 3;
//
//                HE_Face face;
//
//                face.edge = &A;
//                hem->numFaces++;
//
//                A.next = &B;
//                A.previous = &C;
//                A.vertex = &temp_vertex[vertexIndex[1]-1];
//                A.face = &face;
//
//                B.next = &C;
//                B.previous = &A;
//                B.vertex = &temp_vertex[vertexIndex[2]-1];
//                B.face = &face;
//
//                C.next = &A;
//                C.previous = &B;
//                C.vertex = &temp_vertex[vertexIndex[0]-1];
//                C.face = &face;
//
//                edges.push_back(A);
//                edges.push_back(B);
//                edges.push_back(C);
//
//                vertexIndices.push_back(vertexIndex[0]-1);
//                vertexIndices.push_back(vertexIndex[1]-1);
//                vertexIndices.push_back(vertexIndex[2]-1);
//
//                faces.push_back(face);
//
//                sizeOfIndice += 3;
            }
            else if (matches == 12)
            {
                hem->renderingMode = GL_QUADS;
                HE_Edge* A = new HE_Edge(temp_vertex[vertexIndex[0]-1]);
                HE_Edge* B = new HE_Edge(temp_vertex[vertexIndex[1]-1]);
                HE_Edge* C = new HE_Edge(temp_vertex[vertexIndex[2]-1]);;
                HE_Edge* D = new HE_Edge(temp_vertex[vertexIndex[3]-1]);;

                eid+=4;

                hem->numEdges += 4;

                temp_vertex[vertexIndex[0]-1]->edge = A;
                temp_vertex[vertexIndex[1]-1]->edge = B;
                temp_vertex[vertexIndex[2]-1]->edge = C;
                temp_vertex[vertexIndex[3]-1]->edge = D;


                HE_Face* face = new HE_Face();

                hem->numFaces++;

                edges.push_back(A);
                edges.push_back(B);
                edges.push_back(C);
                edges.push_back(D);

                vertexIndices.push_back(vertexIndex[0]-1);
                vertexIndices.push_back(vertexIndex[1]-1);
                vertexIndices.push_back(vertexIndex[2]-1);
                vertexIndices.push_back(vertexIndex[3]-1);

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

    hem->half_edges = new HE_Edge*[edges.size()];
    hem->half_vertex = new HE_Vertex*[temp_vertex.size()];
    hem->half_faces = new HE_Face*[faces.size()];
    hem->indiceBuffer = new int[vertexIndices.size()];

    for(int i = 0; i < faces.size(); i++)
    {
        hem->half_faces[i] = faces[i];
    }

    for (int k = 0; k < temp_vertex.size(); k++)
    {
        hem->half_vertex[k] = temp_vertex[k];
        hem->half_vertex[k]->index = k;
    }

    for(int p = 0; p < vertexIndices.size(); p++)
    {
        hem->indiceBuffer[p] = vertexIndices[p];
    }

    int faceIndex = 0;
    if(hem->renderingMode == GL_QUADS)
    {

        for(int q = 0; q < edges.size(); q+=4)
        {
            hem->half_edges[q]   = edges[q];
            hem->half_edges[q+1] = edges[q+1];
            hem->half_edges[q+2] = edges[q+2];
            hem->half_edges[q+3] = edges[q+3];

            hem->half_edges[q]->face   = hem->half_faces[faceIndex];
            hem->half_edges[q+1]->face = hem->half_faces[faceIndex];
            hem->half_edges[q+2]->face = hem->half_faces[faceIndex];
            hem->half_edges[q+3]->face = hem->half_faces[faceIndex];

            hem->half_edges[q]->next   = hem->half_edges[q+1];
            hem->half_edges[q+1]->next = hem->half_edges[q+2];
            hem->half_edges[q+2]->next = hem->half_edges[q+3];
            hem->half_edges[q+3]->next = hem->half_edges[q];

            hem->half_edges[q]->previous   = hem->half_edges[q+3];
            hem->half_edges[q+1]->previous = hem->half_edges[q];
            hem->half_edges[q+2]->previous = hem->half_edges[q+1];
            hem->half_edges[q+3]->previous = hem->half_edges[q+2];

            hem->half_edges[q]->vertex   = hem->half_vertex[vertexIndices[q]];
            hem->half_edges[q+1]->vertex = hem->half_vertex[vertexIndices[q+1]];
            hem->half_edges[q+2]->vertex = hem->half_vertex[vertexIndices[q+2]];
            hem->half_edges[q+3]->vertex = hem->half_vertex[vertexIndices[q+3]];

            hem->half_vertex[vertexIndices[q]]->edge   = hem->half_edges[q+3];
            hem->half_vertex[vertexIndices[q+1]]->edge = hem->half_edges[q];
            hem->half_vertex[vertexIndices[q+2]]->edge = hem->half_edges[q+1];
            hem->half_vertex[vertexIndices[q+3]]->edge = hem->half_edges[q+2];


            hem->half_faces[faceIndex]->edge = hem->half_edges[q];
            hem->half_faces[faceIndex]->faceID = fid;
            fid++;

            faceIndex++;
        }
    }
    hem->sizeOfBuffer =  vertexIndices.size();

    vertexIndices.clear();
    temp_vertex.clear();
    faces.clear();
    edges.clear();

    hem->SetBuffer(hem->sizeOfBuffer);
    hem->PairEdges();

    return hem;
}

void HE_Mesh::SetBuffer(int count)
{
    Vector4D* buf = new Vector4D[this->numVertex];
    for(int i = 0; i < this->numVertex; i++)
    {
        buf[i] = this->half_vertex[i]->pos;
    }

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, count*sizeof(Vector4D), buf, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32)*count, this->indiceBuffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    delete[] buf;

}


void HE_Mesh::PairEdges()
{
    //At subdivision pairing is wrong! Need to find the double ammount of pairs
    int paired = 0;
    for(int i = 0; i < this->numEdges; i++)
    {
        HE_Edge* edge = this->half_edges[i];
        for(int j = 0; j < this->numEdges; j++)
        {

            if(this->half_edges[i]->next->pair != NULL)
            {
                continue;
            }
            else if(half_edges[i]->vertex == half_edges[j]->vertex && this->half_edges[i]->next->vertex == this->half_edges[j]->previous->vertex)
            {
                half_edges[i]->next->pair = half_edges[j];
                half_edges[j]->pair = half_edges[i]->next;
                paired++;
            }
        }
    }
    std::cout << paired << std::endl;
}

void HE_Mesh::Draw()
{
    glLineWidth(2);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

    glEnableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glPointSize(10);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector4D), NULL);
    glDrawElements(renderingMode, sizeOfBuffer, GL_UNSIGNED_INT, NULL);
    glDrawElements(GL_POINTS, sizeOfBuffer, GL_UNSIGNED_INT, NULL);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

HE_Vertex* HE_Mesh::CalculateFacePoints(HE_Face* face)
{
    float x = 0, y = 0, z = 0;

    int numberOfIterations = 1;
    HE_Edge* start = face->edge;
    HE_Edge* current = start->next;

    x = start->vertex->pos.coordinates[0];
    y = start->vertex->pos.coordinates[1];
    z = start->vertex->pos.coordinates[2];
    while(current != start)
    {
        x += current->vertex->pos.coordinates[0];
        y += current->vertex->pos.coordinates[1];
        z += current->vertex->pos.coordinates[2];
        current = current->next;
        numberOfIterations++;
    }

    float average = 1.0f/numberOfIterations;
    x = x * average;
    y = y * average;
    z = z * average;

    HE_Vertex* facePoint = new HE_Vertex();
    facePoint->pos = Vector4D(x,y,z);
    return facePoint;
}

void HE_Mesh::CalculateEdgePoints(HE_Edge* edge)
{
    HE_Vertex* edgePoint = new HE_Vertex();
    if(edge->pair != nullptr && edge->edgePoint == nullptr)
    {
        HE_Vertex* fp = this->facePoints[edge->face->faceID];
        HE_Vertex* fp2 = this->facePoints[edge->pair->face->faceID];

        Vector4D vertex = edge->vertex->pos;
        Vector4D vertex2 = edge->previous->vertex->pos;


        Vector4D ep = fp->pos + fp2->pos + vertex + vertex2;
        ep = ep/4;
        edgePoint->pos = ep;

        edge->edgePoint = edgePoint;
        edge->pair->edgePoint = edgePoint;

    }
    else
    {
        HE_Vertex* fp = CalculateFacePoints(edge->face);

        Vector4D vertex = edge->vertex->pos;
        Vector4D vertex2 = edge->previous->vertex->pos;

        Vector4D ep = fp->pos + vertex + vertex2;
        ep = ep/3;
        edge->edgePoint = edgePoint;
    }

}

void HE_Mesh::SubDivision()
{
    this->tempVertex = new HE_Vertex*[this->numVertex];

    this->facePoints = new HE_Vertex*[this->numFaces];

    for(int i = 0; i < this->numFaces; i++)
    {
        this->facePoints[i] = CalculateFacePoints(this->half_faces[i]);
    }
    for(int j = 0; j < this->numEdges; j++)
    {
        CalculateEdgePoints(this->half_edges[j]);
    }


    int faceIndex[4];
    int found = 0;

    for(int i = 0; i < this->numVertex; i++)
    {
        HE_Edge** foundEdges = new HE_Edge*[8];
        HE_Vertex* vertex = this->half_vertex[i];

        //Find all adjacent faces to the vertex;
        for(int j = 0; j < this->numFaces; j++)
        {
            HE_Face* f = this->half_faces[j];
            HE_Edge* start = f->edge;
            HE_Edge* current = f->edge->next;
            while(current != start)
            {
                //Find all edges pointing to/from vertex
                if(current->vertex == vertex || start->vertex == vertex)
                {
                    faceIndex[found] = j;
                    foundEdges[found] = current;
                    found++;
                    break;
                }
                else
                {
                    current = current->next;
                }
            }
        }
        Vector4D Q;
        Vector4D R;

        HE_Vertex* fp;
        HE_Vertex* ep;

        for(int k = 0; k < found; k++)
        {
            fp = this->facePoints[faceIndex[k]];
            ep = foundEdges[k]->edgePoint;
            Q = Q + fp->pos;
            R = R + ep->pos;
        }

        Vector4D vertexPosition;
        Q = Q/found;
        R = (R*2)/found;

        Vector4D temp = vertex->pos;
        temp = (temp *(found - 3)) / found;
        vertexPosition = Q + R;
        vertexPosition = vertexPosition + temp;

        HE_Vertex* verticePoint = new HE_Vertex();
        verticePoint->pos = vertexPosition;
        verticePoint->index = i;
        this->tempVertex[i] = verticePoint;
        found = 0;
        delete[] foundEdges;

    }
}


void HE_Mesh::SetupEdges()
{
    this->tempEdges = new HE_Edge*[this->numEdges*4];
    this->tempFaces = new HE_Face*[this->numFaces*4];
    int addIndex = 0;
    int faceIndex = 0;
    for(int i = 0; i < this->numEdges; i+=4)
    {
        HE_Face* face = new HE_Face();
        int id = this->half_edges[i]->vertex->index;
        this->tempEdges[addIndex]   = new HE_Edge(this->tempVertex[this->half_edges[i]->vertex->index]); //<< Point edge to the new vertex
        this->tempEdges[addIndex+1] = new HE_Edge(this->half_edges[i]->next->edgePoint);
        this->tempEdges[addIndex+2] = new HE_Edge(this->facePoints[this->half_edges[i]->face->faceID]);
        this->tempEdges[addIndex+3] = new HE_Edge(this->half_edges[i]->edgePoint); //<< Point edge to its edgepoint


        this->tempEdges[addIndex]->next   = this->tempEdges[addIndex+1];
        this->tempEdges[addIndex+1]->next = this->tempEdges[addIndex+2];
        this->tempEdges[addIndex+2]->next = this->tempEdges[addIndex+3];
        this->tempEdges[addIndex+3]->next = this->tempEdges[addIndex];

        this->tempEdges[addIndex]->previous   = this->tempEdges[addIndex+3];
        this->tempEdges[addIndex+1]->previous = this->tempEdges[addIndex];
        this->tempEdges[addIndex+2]->previous = this->tempEdges[addIndex+1];
        this->tempEdges[addIndex+3]->previous = this->tempEdges[addIndex+2];

        this->tempEdges[addIndex]->face   = face;
        this->tempEdges[addIndex+1]->face = face;
        this->tempEdges[addIndex+2]->face = face;
        this->tempEdges[addIndex+3]->face = face;

        this->tempEdges[addIndex]->id   = addIndex;
        this->tempEdges[addIndex+1]->id = addIndex + 1;
        this->tempEdges[addIndex+2]->id = addIndex + 2;
        this->tempEdges[addIndex+3]->id = addIndex + 3;

        face->faceID = i;
        face->edge = this->tempEdges[addIndex];
        this->tempFaces[faceIndex] = face;
        addIndex += 4;
        faceIndex++;
    }



    for(int j = 0; j < this->numEdges; j++)
    {
        delete this->half_edges[j];
    }
    for(int k = 0; k < this->numFaces; k++)
    {
        delete this->half_faces[k];
    }
    for(int l = 0; l < this->numVertex; l++)
    {
        delete this->half_vertex[l];
    }


    delete[] this->half_edges;
    delete[] this->half_faces;
    delete[] this->half_vertex;
    delete[] this->indiceBuffer;

    this->numEdges *= 4;
    this->numFaces *= 4;
    this->half_faces = new HE_Face*[this->numFaces];
    this->half_edges = new HE_Edge*[this->numEdges];


//    memcpy(this->half_faces, this->tempFaces,sizeof(*this->tempFaces)*this->numFaces);
//    memcpy(this->half_edges, this->tempEdges,sizeof(*this->tempEdges)*this->numEdges);

    this->numVertex = this->numFaces+ this->numVertex + this->numEdges*0.5;



//    for(int j = 0; j < this->numEdges; j++)
//    {
//        this->half_edges[j] = this->tempEdges[j];
////        delete this->tempEdges[j];
//    }
//    for(int k = 0; k < this->numFaces; k++)
//    {
//        delete this->tempFaces[k];
//    }
//    int bla = 0;
    delete[] this->tempEdges;
    delete[] this->tempFaces;

    this->half_vertex = new HE_Vertex*[this->numVertex];

    this->sizeOfBuffer = this->numFaces*4;
    this->indiceBuffer = new int[this->sizeOfBuffer];

    PairEdges();

    int add = 0;
    int ib = 0;
    for(int i = 0; i < this->numEdges; i++)
    {
        HE_Edge* edge = this->half_edges[i];
        if(!edge->vertex->added)
        {
            this->half_vertex[add] = this->half_edges[i]->vertex;
            this->indiceBuffer[ib] = this->half_edges[i]->id;
            this->half_edges[i]->vertex->added = true;
            add++;
            ib++;
        }
        else
        {
            this->indiceBuffer[ib] = this->half_edges[i]->pair->id;
            ib++;
        }
    }
    SetBuffer(this->sizeOfBuffer);
}

