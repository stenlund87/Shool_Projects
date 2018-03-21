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
    Vector4D temp[8];
};


struct PhysicsProperties
{
    Vector4D centerOfMass;
    Vector4D momentum;
    Vector4D force;
    Vector4D velocity;
    Vector4D torque;
    Vector4D spinVector;
    Vector4D angularMomentum;

    Matrix4D skewMatrix;
    Matrix4D inersiaTension;
    Matrix4D inverseInersiaTension;
    Matrix4D shapeMatrix;

    float mass; //In kg

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

    void SetBoxPosition(Vector4D pos);

    void ReturnBoxPosition();

    void CalculateAABB(Matrix4D rot);

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

    /*Buffers*/
    Vertex *verticeBuffer;
    int *indiceBuffer;
    int sizeOfBuffer;
    Vector4D meshColor;
    Plane plane[6];
    Vector4D intersectPoint;
    Vector4D color;
    Matrix4D model, rotation, translation , scale;
    int width;
    AABB box;
    bool selected = false;
    bool once = false;

    Vector4D tempMin;
    Vector4D tempMax;

    PhysicsProperties physics;
};


#endif // !MESHRESOURCE_H