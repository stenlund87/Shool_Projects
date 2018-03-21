#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include <vector>
#include "GL/glew.h"
#include "vm_mathlib.h"



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

    Vertex(Vector4D p)
    {
        pos = p;
    }

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

    Vector4D operator+(const Vertex& rhs)
    {
        return (pos + rhs.pos);
    }

    const bool operator==(const Vertex& rhs)
    {
        return (pos == rhs.pos);
    }
    const bool operator!=(const Vertex& rhs)
    {
        return (pos != rhs.pos);
    }
    Vector4D operator-(const Vertex& rhs)
    {
        return (pos - rhs.pos);
    }

    void operator=(const Vector4D& rhs)
    {
        pos = rhs;
    }
        float& operator[](int i)
    {
        return pos[i];
    }

    /* Vector4D to represent position and uv-coordinates */
    Vector4D pos;
    Vector4D uv;
    Vector4D normal;
};

struct Edge
{
    Vector4D start;
    Vector4D end;
    Edge* next;
};

struct Face
{
    Face(){edge = nullptr;};
    ~Face()
    {
        edge = nullptr;
    };
    Edge* edge;
};

struct AABB
{
    Vector4D min;
    Vector4D max;
    Vector4D temp[8];
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

    void SetBoxPosition(Vector4D pos);

    void ReturnBoxPosition();

    void CalculateAABB();

    void CalculateModelMatrix();

    void Momentum();

    void InertiaTensor();
    void InverseInertiaTensor();
    void DeltaRotation(Vector4D spin);
    void Update(Vector4D collision, float dt);
    Vector4D GetFarthestPointInDirection(Vector4D dir);

    /* Render data */
    GLuint vao, vbo, ebo;

    /* Size data */
//	const int floatsPerPosition = 3;
//	const int floatsPerColor = 4;
    const int numVertices = 8;
    int num = 0;

    /*Buffers*/
    Vertex *verticeBuffer;
//    Vertex* tempBuffer;
    int *indiceBuffer;
//    int* tempIndice;
    int sizeOfBuffer;
    Vector4D intersectPoint;
    Matrix4D model, rotation, translation , scale;
    int width;
    AABB box;
    bool wireframe = false;
    bool once = false;
    std::vector<Edge*> edges;
    std::vector<Face*> faces;

    Vector4D tempMin;
    Vector4D tempMax;

};


#endif // !MESHRESOURCE_H