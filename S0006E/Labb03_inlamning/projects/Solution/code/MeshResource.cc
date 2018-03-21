#pragma	once
#include "MeshResource.h"
#include "config.h"




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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indiceBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

MeshResource MeshResource::MakeCube(float width, float height, float depth)
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


	mesh->SetBO(mesh->verticeBuffer, 8);

	return *mesh;
}


//static MeshResource MeshResource::MakeCube()
//{
//	Vertex* vBuffer = new Vertex[8];
//	int* intBuffer = new int[36];
//
//	Vertex topLeft(-0.25f, +0.25f, +0.25f);
//	Vertex topRight(+0.25f, +0.25f, +0.25f);
//	Vertex bottomLeft(-0.25f, -0.25f, +0.25f);
//	Vertex bottomRight(+0.25f, -0.25f, +0.25f);
//
//	Vertex backsideTopLeft(-0.25f, +0.25f, -0.25f);
//	Vertex backsideTopRight(+0.25f, +0.25f, -0.25f);
//	Vertex backsideBottomLeft(-0.25f, -0.25f, -0.25f);
//	Vertex backsideBottomRight(+0.25f, -0.25f, -0.25f);
//
//	Vector4D uv1_bl(0, 0, 0, 0);
//	Vector4D uv2_tl(0, 1, 1, 1);
//	Vector4D uv3_br(1, 0, 0, 1);
//	Vector4D uv4_tr(1, 1, 1, 1);
//
//
//	backsideTopLeft.uv = uv2_tl;
//	backsideBottomRight.uv = uv3_br;
//	backsideBottomLeft.uv = uv1_bl;
//	backsideTopRight.uv = uv4_tr;
//
//	topLeft.uv = uv2_tl;
//	bottomRight.uv = uv3_br;
//	bottomLeft.uv = uv1_bl;
//	topRight.uv = uv4_tr;
//
//
//	vBuffer[0] = backsideTopLeft;
//	vBuffer[1] = backsideBottomRight;
//	vBuffer[2] = backsideBottomLeft;
//	vBuffer[3] = backsideTopRight;
//
//	vBuffer[4] = topLeft;
//	vBuffer[5] = bottomRight;
//	vBuffer[6] = bottomLeft;
//	vBuffer[7] = topRight;
//
//
//	intBuffer[0] = 3;
//	intBuffer[1] = 2;
//	intBuffer[2] = 1;
//	intBuffer[3] = 0;
//	intBuffer[4] = 2;
//	intBuffer[5] = 3;
//
//	intBuffer[6] = 7;
//	intBuffer[7] = 1;
//	intBuffer[8] = 5;
//	intBuffer[9] = 3;
//	intBuffer[10] = 1;
//	intBuffer[11] = 7;
//
//	intBuffer[12] = 4;
//	intBuffer[13] = 5;
//	intBuffer[14] = 6;
//	intBuffer[15] = 7;
//	intBuffer[16] = 5;
//	intBuffer[17] = 4;
//
//	intBuffer[18] = 0;
//	intBuffer[19] = 6;
//	intBuffer[20] = 2;
//	intBuffer[21] = 4;
//	intBuffer[22] = 6;
//	intBuffer[23] = 0;
//
//	intBuffer[24] = 6;
//	intBuffer[25] = 1;
//	intBuffer[26] = 2;
//	intBuffer[27] = 5;
//	intBuffer[28] = 1;
//	intBuffer[29] = 6;
//
//	intBuffer[30] = 0;
//	intBuffer[31] = 7;
//	intBuffer[32] = 4;
//	intBuffer[33] = 3;
//	intBuffer[34] = 7;
//	intBuffer[35] = 0;
//}


MeshResource MeshResource::MakeCube()
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

	//Vector4D uv1_bl(0, 0, 0, 0);
	//Vector4D uv2_tl(0, 1, 0, 1);
	//Vector4D uv3_br(1, 0, 1, 0);
	//Vector4D uv4_tr(1, 1, 1, 1);

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

	//backsideTopLeft.uv = uv2_tl;
	//backsideBottomRight.uv = uv3_br;
	//backsideBottomLeft.uv = uv1_bl;
	//backsideTopRight.uv = uv4_tr;

	//topLeft.uv = uv2_tl;
	//bottomRight.uv = uv3_br;
	//bottomLeft.uv = uv1_bl;
	//topRight.uv = uv4_tr;


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
	mesh->SetBO(mesh->verticeBuffer, 8);

	return *mesh;
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

	this->SetBO(verticeBuffer, 4);

	//delete verticeBuffer;
	//delete indiceBuffer;
}


void MeshResource::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 8, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 8, (GLvoid*)(sizeof(float32) * 4));


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
