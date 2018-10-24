#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include <vector>
#include "GL\glew.h"
#include "vm_mathlib.h"
#include <intsafe.h>
//#include "core/app.h"


/**
*
*/
struct Vertex
{
	/**
	*
	*/
	Vertex()
	{
		pos.Set(0, 0, 0);
	};

	/**
	*Method to set position for the Vertex
	*@param x,y,z of type GLfloat
	*/
	Vertex(GLfloat x, GLfloat y, GLfloat  z)
	{
		pos.Set(x, y, z);
	}
	//~Vertex();

	Vector4D pos;
	Vector4D color;
};


class MeshResource
{
public:
	MeshResource();
	~MeshResource();

	/* Mesh methods */
	void MakeQuad();

	void DrawQuad();

	void SetVBO();

	void SetEBO();

	void Draw();

	/* Render data */
	GLuint vao, vbo, ebo;

	const int floatsPerPosition = 3;
	const int floatsPerColor = 4;
	const int numVertices = 4;
	const int sizeOfPositions = sizeof(float) * numVertices * floatsPerPosition;
	const int sizeOfColors = sizeof(float) * numVertices * floatsPerColor;
	const int numIndices = 4;
	const int sizeOfIndices = sizeof(Vertex) * numIndices;
	const int indicesSize = sizeof(INT32)*6;


	Vertex *verticeBuffer;
	int *indiceBuffer;
	Matrix4D test;

	/* Functions */
	
};


MeshResource::MeshResource()
{

}

MeshResource::~MeshResource()
{

}

/**
* Method to set the VBO 
*/

void MeshResource::SetVBO()
{

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeOfIndices, verticeBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshResource::SetEBO()
{

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indiceBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void MeshResource::MakeQuad()
{

	verticeBuffer = new Vertex[4];
	indiceBuffer = new int[6];

	Vertex topLeft(-0.25f, 0.25f, 0.0f);
	Vertex topRight(0.25f, 0.25f, 0.0f);
	Vertex bottomLeft(-0.25f, -0.25f, 0.0f);
	Vertex bottomRight(0.25f, -0.25f, 0.0f);


	//Vertex topLeft(-0.5f, 0.5f, 0.0f);
	//Vertex topRight(0.5f, 0.5f, 0.0f);
	//Vertex bottomLeft(-0.5f, -0.5f, 0.0f);
	//Vertex bottomRight(0.5f, -0.5f, 0.0f);


	Vector4D a(0, 0, 1, 1);
	Vector4D b(0, 1, 0, 1);
	//float b[4] = { 0.0,1.0,0.0,0.0 };
	//float a[4] = { 0.0,0.0,1.0,0.0 };

	topLeft.color = { 0.0f, 1.0f, 0.0f , 1.0f };
	topRight.color = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomLeft.color = { 0.0f, 0.0f, 1.0f, 1.0f };
	bottomRight.color = { 0.0f, 1.0f, 0.0f , 1.0f };


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
}

void MeshResource::DrawQuad()
{
}

void MeshResource::Draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
}

#endif // !MESHRESOURCE_H