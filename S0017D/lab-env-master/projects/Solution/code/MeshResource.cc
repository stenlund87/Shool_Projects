//#pragma	once
#include "MeshResource.h"
#include "config.h"
#include <map>
#include <string.h>




MeshResource::MeshResource()
{

}

MeshResource::~MeshResource()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1,&ebo);
	delete[] this->verticeBuffer;
	delete[] this->indiceBuffer;
	//delete verticeBuffer;
	//delete indiceBuffer;
	verticeBuffer = nullptr;
	indiceBuffer = nullptr;
}	

/**
* Method to set the VBO
*/
void MeshResource::SetBO(Vertex* buffer, unsigned int count)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), buffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32)*count, indiceBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

MeshResource* MeshResource::MakeCube(float width, float height, float depth)
{
	MeshResource* mesh = new MeshResource();

	mesh->verticeBuffer = new Vertex[8];
	mesh->indiceBuffer = new int[36];

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

	mesh->verticeBuffer[0] = backsideTopLeft;
	mesh->verticeBuffer[1] = backsideBottomRight;
	mesh->verticeBuffer[2] = backsideBottomLeft;
	mesh->verticeBuffer[3] = backsideTopRight;

	mesh->verticeBuffer[4] = topLeft;
	mesh->verticeBuffer[5] = bottomRight;
	mesh->verticeBuffer[6] = bottomLeft;
	mesh->verticeBuffer[7] = topRight;


	mesh->indiceBuffer[0] = 3;
	mesh->indiceBuffer[1] = 2;
	mesh->indiceBuffer[2] = 1;
	mesh->indiceBuffer[3] = 0;
	mesh->indiceBuffer[4] = 2;
	mesh->indiceBuffer[5] = 3;

	mesh->indiceBuffer[6] = 7;
	mesh->indiceBuffer[7] = 1;
	mesh->indiceBuffer[8] = 5;
	mesh->indiceBuffer[9] = 3;
	mesh->indiceBuffer[10] = 1;
	mesh->indiceBuffer[11] = 7;

	mesh->indiceBuffer[12] = 4;
	mesh->indiceBuffer[13] = 5;
	mesh->indiceBuffer[14] = 6;
	mesh->indiceBuffer[15] = 7;
	mesh->indiceBuffer[16] = 5;
	mesh->indiceBuffer[17] = 4;

	mesh->indiceBuffer[18] = 0;
	mesh->indiceBuffer[19] = 6;
	mesh->indiceBuffer[20] = 2;
	mesh->indiceBuffer[21] = 4;
	mesh->indiceBuffer[22] = 6;
	mesh->indiceBuffer[23] = 0;

	mesh->indiceBuffer[24] = 6;
	mesh->indiceBuffer[25] = 1;
	mesh->indiceBuffer[26] = 2;
	mesh->indiceBuffer[27] = 5;
	mesh->indiceBuffer[28] = 1;
	mesh->indiceBuffer[29] = 6;

	mesh->indiceBuffer[30] = 0;
	mesh->indiceBuffer[31] = 7;
	mesh->indiceBuffer[32] = 4;
	mesh->indiceBuffer[33] = 3;
	mesh->indiceBuffer[34] = 7;
	mesh->indiceBuffer[35] = 0;

	mesh->sizeOfBuffer = 36;
	mesh->SetBO(mesh->verticeBuffer, 8);

	return mesh;
}


MeshResource* MeshResource::MakeCube()
{
	MeshResource* mesh = new MeshResource();

	mesh->verticeBuffer = new Vertex[8];
	mesh->indiceBuffer = new int[36];

	Vertex topLeft(-0.25f, +0.25f, +0.25f);
	Vertex topRight(+0.25f, +0.25f, +0.25f);
	Vertex bottomLeft(-0.25f, -0.25f, +0.25f);
	Vertex bottomRight(+0.25f, -0.25f, +0.25f);

	Vertex backsideTopLeft(-0.25f, +0.25f, -0.25f);
	Vertex backsideTopRight(+0.25f, +0.25f, -0.25f);
	Vertex backsideBottomLeft(-0.25f, -0.25f, -0.25f);
	Vertex backsideBottomRight(+0.25f, -0.25f, -0.25f);

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

	mesh->verticeBuffer[0] = backsideTopLeft;
	mesh->verticeBuffer[1] = backsideBottomRight;
	mesh->verticeBuffer[2] = backsideBottomLeft;
	mesh->verticeBuffer[3] = backsideTopRight;

	mesh->verticeBuffer[4] = topLeft;
	mesh->verticeBuffer[5] = bottomRight;
	mesh->verticeBuffer[6] = bottomLeft;
	mesh->verticeBuffer[7] = topRight;


	mesh->indiceBuffer[0] = 3;
	mesh->indiceBuffer[1] = 2;
	mesh->indiceBuffer[2] = 1;
	mesh->indiceBuffer[3] = 0;
	mesh->indiceBuffer[4] = 2;
	mesh->indiceBuffer[5] = 3;

	mesh->indiceBuffer[6] = 7;
	mesh->indiceBuffer[7] = 1;
	mesh->indiceBuffer[8] = 5;
	mesh->indiceBuffer[9] = 3;
	mesh->indiceBuffer[10] = 1;
	mesh->indiceBuffer[11] = 7;

	mesh->indiceBuffer[12] = 4;
	mesh->indiceBuffer[13] = 5;
	mesh->indiceBuffer[14] = 6;
	mesh->indiceBuffer[15] = 7;
	mesh->indiceBuffer[16] = 5;
	mesh->indiceBuffer[17] = 4;

	mesh->indiceBuffer[18] = 0;
	mesh->indiceBuffer[19] = 6;
	mesh->indiceBuffer[20] = 2;
	mesh->indiceBuffer[21] = 4;
	mesh->indiceBuffer[22] = 6;
	mesh->indiceBuffer[23] = 0;

	mesh->indiceBuffer[24] = 6;
	mesh->indiceBuffer[25] = 1;
	mesh->indiceBuffer[26] = 2;
	mesh->indiceBuffer[27] = 5;
	mesh->indiceBuffer[28] = 1;
	mesh->indiceBuffer[29] = 6;

	mesh->indiceBuffer[30] = 0;
	mesh->indiceBuffer[31] = 7;
	mesh->indiceBuffer[32] = 4;
	mesh->indiceBuffer[33] = 3;
	mesh->indiceBuffer[34] = 7;
	mesh->indiceBuffer[35] = 0;

	mesh->sizeOfBuffer = 36;
	mesh->SetBO(mesh->verticeBuffer, 8);

	return mesh;
}


void MeshResource::MakeQuad()
{

	verticeBuffer = new Vertex[4];
	indiceBuffer = new int[6];

	Vertex topLeft(-0.25f, 0.25f, 0.0f);
	Vertex topRight(0.25f, 0.25f, 0.0f);
	Vertex bottomLeft(-0.25f, -0.25f, 0.0f);
	Vertex bottomRight(0.25f, -0.25f, 0.0f);

	Vector4D a(0, 0, 1, 1);
	Vector4D b(0, 1, 0, 1);


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
	this->SetBO(verticeBuffer, 4);
}


void MeshResource::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 12, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 12, (GLvoid*)(sizeof(float32) * 4));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 12, (GLvoid*)(sizeof(float32) * 8));


	glDrawElements(GL_TRIANGLES, sizeOfBuffer/3, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


MeshResource* MeshResource::Load(const char* filename)
{
	MeshResource* mesh = new MeshResource();
	int sizeOfIndice = 0;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector<Vertex> test;
	std::vector<Vector4D>temp_vertices;
	std::vector<Vector4D> temp_uvs;
	std::vector<Vector4D> temp_normals;


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
			Vector4D vertex;
			fscanf(myfile, "%f %f %f\n", vertex[0], vertex[1], vertex[2]);
			vertex = vertex *0.003f;
			temp_vertices.push_back(vertex);
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

	mesh->verticeBuffer = new Vertex[finalVertex.size()];
	mesh->indiceBuffer = new int[finalVertex.size()];
	for (int k = 0; k < finalVertex.size(); k++)
	{
		mesh->verticeBuffer[k] = finalVertex[k];
		mesh->indiceBuffer[k] = buffer[k];
	}
	mesh->sizeOfBuffer = finalVertex.size();
	mesh->SetBO(mesh->verticeBuffer, finalVertex.size());
	return mesh;
}