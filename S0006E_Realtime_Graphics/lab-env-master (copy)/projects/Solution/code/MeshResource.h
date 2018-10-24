#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include <vector>
#include "GL\glew.h"
#include "vm_mathlib.h"
#include <intsafe.h>


/**
*Struct that represent a vertex that has a position and uv-coordinates
*/
struct Vertex
{
	/**
	*Default constructor that sets position to 0,0,0
	*/
	Vertex()
	{
		pos.Set(0, 0, 0);
	};

	~Vertex()
	{
	}

	/**
	*Method to set position for the Vertex
	*@param x,y,z of type GLfloat
	*/
	Vertex(GLfloat x, GLfloat y, GLfloat  z)
	{
		pos.Set(x, y, z);
	}

	/* Vector4D to represent position and uv-coordinates */
	Vector4D pos;
	Vector4D uv;
	Vector4D normal;
};


class MeshResource
{

public:
	MeshResource();
	~MeshResource();

	/*Mesh methods */

	/**
	*Method to make a cube of size 0.25
	@return a new MeshResource object
	*/
	static MeshResource* MakeCube();

	/**
	*Method to make a cube with the size of your own choosing
	@param float width, float height, float depth
	@return a new MeshResource object
	*/
	static MeshResource* MakeCube(float width, float height, float depth);

	/**
	*Method to make a square
	*/
	void MakeQuad();

	static MeshResource* SetupQuad(float width);

	/**
	*Method to set the Buffers
	@param Vertex* buffer, unsigned in count
	*/
	void SetBO(Vertex * buffer, unsigned int count);

	/**
	*Method to draw the shape
	*/
	void Draw();

	static MeshResource* LoadObj(const char* filename);
	static MeshResource* Load(const char* filename);

	/* Render data */
	GLuint vao, vbo, ebo;

	/* Size data */
	const int floatsPerPosition = 3;
	const int floatsPerColor = 4;
	int numVertices = 8;


	/*Buffers*/
	Vertex *verticeBuffer;
	int *indiceBuffer;	
	int sizeOfBuffer;
};


#endif // !MESHRESOURCE_H