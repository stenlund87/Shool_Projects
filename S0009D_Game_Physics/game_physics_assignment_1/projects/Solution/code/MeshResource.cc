#pragma	once
#include "MeshResource.h"
#include "config.h"
#include <map>
#include <string.h>

MeshResource::MeshResource()
{
	this->plane = Plane();
	this->plane.center = Vector4D(0,0,0);
	this->plane.normal = Vector4D(0,0,1);
	meshColor = Vector4D(1,0,0);
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

MeshResource::MeshResource(Plane p)
{
	this->plane = p;
	this->plane.center = Vector4D(0,0,0);
	this->plane.normal = Vector4D(0,0,-1);
	meshColor = Vector4D(1,0,0);
}

/**
* Method to set the VBO
*/
void MeshResource::SetBO()
{

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->sizeOfBuffer * sizeof(Vertex), this->verticeBuffer, GL_STATIC_DRAW);
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
	this->plane.center = Vector4D(0,0,0);
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

	plane.quadWidth = 0.25;

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
	this->model.Set_Position(pos);
	this->plane.center = pos;
	this->plane.normal = Vector4D(0,0,1);
	verticeBuffer = new Vertex[4];
	indiceBuffer = new int[6];
	this->plane.quadWidth = size;


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

	topLeft.color = { 1.0f, 0.0f, 0.0f , 1.0f };
	topRight.color = { 1.0f, 0.0f, 0.0f, 1.0f };
	bottomLeft.color = { 1.0f, 0.0f, 0.0f, 1.0f };
	bottomRight.color = { 1.0f, 0.0f, 0.0f , 1.0f };


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
	plane.quadWidth = 0.25;

	Vertex topLeft(-0.25f, 0.25f, 0.0f);
	Vertex topRight(0.25f, 0.25f, 0.0f);
	Vertex bottomLeft(-0.25f, -0.25f, 0.0f);
	Vertex bottomRight(0.25f, -0.25f, 0.0f);


	topLeft.uv = { 0.0f, 1.0f, 0.0f , 1.0f };
	topRight.uv = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomLeft.uv = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomRight.uv = { 0.0f, 1.0f, 0.0f , 1.0f };

	topLeft.color = { 1.0f, 0.0f, 0.0f , 1.0f };
	topRight.color = { 1.0f, 0.0f, 0.0f, 1.0f };
	bottomLeft.color = { 1.0f, 0.0f, 0.0f, 1.0f };
	bottomRight.color = { 1.0f, 0.0f, 0.0f , 1.0f };


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
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 16, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 16, (GLvoid*)(sizeof(float32) * 4));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 16, (GLvoid*)(sizeof(float32) * 8));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 16, (GLvoid*)(sizeof(float32) * 12));

	glDrawElements(GL_TRIANGLES, sizeOfBuffer, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	this->DrawBorders();

}

void MeshResource::Load(const char* filename)
{
	int sizeOfIndice = 0;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector<Vertex> test;
	std::vector<Vector4D>temp_vertices;
	std::vector<Vector4D> temp_uvs;
	std::vector<Vector4D> temp_normals;


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
			float x = 0, y = 0, z = 0;
			Vector4D vertex;
			fscanf(myfile, "%f %f %f\n", &vertex[0],&vertex[1] , &vertex[2]);

//			vertex = vertex *0.003f;
//            vertex = vertex*0.5;
			temp_vertices.push_back(vertex);
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
			fscanf(myfile, "%f %f %f\n", &normal[0], &normal[1],& normal[2]);
			temp_normals.push_back(normal);
		}

		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(myfile, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);


			if (matches == 9)
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
				sizeOfIndice += 3;
			}

			else if (matches == 12)
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);


				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[2]);
				uvIndices.push_back(uvIndex[3]);


				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[2]);
				normalIndices.push_back(normalIndex[3]);
				sizeOfIndice += 4;
			}
			else
			{
					std::cout << "Cant load file with this parser";
					std::cout << matches << std::endl;
			}
		}
	}

	std::vector<Vertex> finalVertex;
	std::vector<int> buffer;

	int p = 0;

	for (int i = 0; i < vertexIndices.size(); i++)
	{
		Vertex ver;
		ver.pos = temp_vertices[vertexIndices[i] - 1];
		ver.uv = temp_uvs[uvIndices[i] - 1];
		ver.normal = temp_normals[normalIndices[i] - 1];
		finalVertex.push_back(ver);
		buffer.push_back(p);
		p++;

	}

	this->verticeBuffer = new Vertex[finalVertex.size()];
	this->indiceBuffer = new int[finalVertex.size()];
	for (int k = 0; k < finalVertex.size(); k++)
	{
		if(finalVertex[k].pos[0] < minimum[0]){minimum[0] = finalVertex[k].pos[0];}
		else if(finalVertex[k].pos[0] > maximum[0]){maximum[0] = finalVertex[k].pos[0];}

		if(finalVertex[k].pos[1] > minimum[1]){minimum[1] = finalVertex[k].pos[1];}
		else if(finalVertex[k].pos[1] < maximum[1]){maximum[1] = finalVertex[k].pos[1];}

		if(finalVertex[k].pos[2] < minimum[2]){minimum[2] = finalVertex[k].pos[2];}
		else if(finalVertex[k].pos[2] > maximum[2]){maximum[2] = finalVertex[k].pos[2];}

		this->verticeBuffer[k] = finalVertex[k];
		this->indiceBuffer[k] = buffer[k];
	}
	this->sizeOfBuffer = finalVertex.size();

	this->box.max = maximum;
	this->box.min = minimum;
	this->SetBO();
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
	this->plane.center = pos;
	this->model.Set_Position(pos);
	this->plane.normal = Vector4D(0,0,1);
}

void MeshResource::CalculateAABB()
{

}
