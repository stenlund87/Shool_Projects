#ifndef GSCEPT_LAB_ENV_HE_MESH_H
#define GSCEPT_LAB_ENV_HE_MESH_H


#include <vector>
#include "GL/glew.h"
#include <vm_mathlib.h>
#include "MeshResource.h"

struct HE_Face;
struct HE_Edge;
struct HE_Vertex;


struct HE_Face
{
    HE_Face(){edge = nullptr;};
    ~HE_Face()
    {
        edge = nullptr;
    };
    HE_Edge* edge;
    int faceID;
};


struct HE_Vertex
{

    HE_Vertex(){};
    HE_Vertex(Vector4D vertex, HE_Edge* ed)
    {
        pos = vertex;
        edge = ed;
    };
    ~HE_Vertex()
    {
    };
    Vector4D pos;
//    Vector4D normal;
//    Vector4D uv;
    HE_Edge* edge = nullptr; //<< One of the edges emantating from the vertex
    int index;
    bool added = false;
};

struct HE_Edge
{
    HE_Edge(){};
    HE_Edge(HE_Vertex* v)
    {
        vertex = v;
    };
    ~HE_Edge()
    {
        vertex = nullptr;
        pair = nullptr;
        face = nullptr;
        next = nullptr;
    };
    HE_Vertex* vertex = nullptr; //<< Vertex at the end of the half-edge
    HE_Edge* pair = nullptr; //<< Oppositely oriented adjecent half-edge
    HE_Face* face = nullptr; //<< Face of the half-edge borders
    HE_Edge* next = nullptr; //<< Next helf-edge around the face
    HE_Edge* previous = nullptr;

    HE_Vertex* edgePoint = nullptr;
    int id;
};


class HE_Mesh
{
public:
    HE_Mesh();
    ~HE_Mesh();

    static HE_Mesh* LoadFromFile(const char* filename);

    void SetBuffer(int count);
    void PairEdges();
    void Draw();
    HE_Vertex* CalculateFacePoints(HE_Face* face);
    void CalculateEdgePoints(HE_Edge* edge);
    std::vector<HE_Vertex> CalculateVertexPoints(HE_Vertex ver);
    void SubDivision();
    void SetupEdges();

    HE_Edge** half_edges;
    HE_Vertex** half_vertex;
    HE_Face** half_faces;
    int* indiceBuffer;

    HE_Edge** tempEdges;
    HE_Vertex** tempVertex;
    HE_Face** tempFaces;

    HE_Vertex** facePoints;

    int sizeOfBuffer = 0, numFaces = 0, numVertex = 0, numEdges = 0;
    GLuint vao, vbo, ebo;

    GLenum renderingMode;

private:

};

#endif //GSCEPT_LAB_ENV_HE_MESH_H
