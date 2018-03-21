#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include <vector>
#include "GL/glew.h"
#include "Plane.h"


struct HE_Edge;

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
	Vector4D color;
};

struct AABB
{
	Vector4D min;
	Vector4D max;
};


class MeshResource
{

public:
	MeshResource();
	~MeshResource();
	MeshResource(Plane p);

	/*Mesh methods */

	/**
	*Method to make a cube of size 0.25
	@return a new MeshResource object
	*/
	void MakeCube();

	/**
	*Method to make a cube with the size of your own choosing
	@param float width, float height, float depth
	@return a new MeshResource object
	*/
	void MakeCube(float width, float height, float depth);

	/**
	*Method to make a square
	*/
	void MakeQuad();

	void MakeQuad(float size, Vector4D pos);

	/**
	*Method to set the Buffers
	@param Vertex* buffer, unsigned in count
	*/
	void SetBO();

	/**
	*Method to draw the shape
	*/
	void Draw();

	void DrawBorders();

	void Load(const char* filename);

	void SetPosition(Vector4D pos);

	void CalculateAABB();

	/* Render data */
	GLuint vao, vbo, ebo;

	/* Size data */
//	const int floatsPerPosition = 3;
//	const int floatsPerColor = 4;
	const int numVertices = 8;

	/*Buffers*/
	Vertex *verticeBuffer;
	int *indiceBuffer;	
	int sizeOfBuffer;
	Vector4D meshColor;
	Plane plane;
	Vector4D intersectPoint;
	Vector4D color;
	Matrix4D model;
	int width;
	AABB box;
	bool selected = false;
};


#endif // !MESHRESOURCE_H