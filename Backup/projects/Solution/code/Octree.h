//
// Created by ponste-5 on 1/22/18.
//

#ifndef TETRAHEDRAL_MESH_OCTREE_H
#define TETRAHEDRAL_MESH_OCTREE_H
#include <vector>
#include "MeshResource.h"



struct Tetrahedra
{
    Tetrahedra()
    {
        vBuff = new Vertex[4];
        iBuff = new int[12];
    }
    Vertex* vBuff;
    int* iBuff;
};

/*!Child nodes*/
struct OctreeNode
{
    OctreeNode()
    {
//        data.pos = Vector4D(100,100,100);
    };

    OctreeNode(Vertex value)
    {
        data = value;
        edge = new Edge*[12];
        face = new Face*[6];
    };
    ~OctreeNode()
    {
    };

    Vertex data;
    Edge** edge;
    int numEdges = 0;
    int numFaces = 0;
    Vertex* tetrahedrons;
    Face** face;
    Vertex* edgePoint = nullptr;
    Vertex* facePoint = nullptr;
};

class Octree
{
public:
    //Default Constructor
    Octree();
    //Construct the tree with a Vertex buffer
    Octree(float x, float y, float z, Octree* p);
    Octree(MeshResource& mesh);
    Octree(AABB& box, Vertex* buff, std::vector<Edge*>& e, std::vector<Face*>& f, const int numV, MeshResource* mesh);
    ~Octree();	//<Destructor
    void SetuDimensions(float w, float h, float d);	//<Set witdth and height for the whole tree
    bool InsertVertex(Vertex& v,const int& numVert, const int& numSplits);										//<Insert element(leaf) in tree
    void FindElement(Vertex v);	//<Finds element in the tree
    bool FindAndInsert(Vector4D v, Edge* e);
    bool FindAndInsert(Vector4D v, Face* f);
    void Split(Octree* p);	//< Split the tree
    void DrawTree();
    void InitiateTetrahedra(std::vector<Vertex>& vBuff, std::vector<int>& iBuff);
    bool Cleanup();
    void CalculateEdgeVertex();
    void CalculateFaceVertex();

    void FixBuffer(std::vector<Vertex>& vBuff, std::vector<int>& iBuff);
    void DrawPoints(std::vector<Vector4D>& points);


private:
    Octree* ftl = nullptr;
    Octree* ftr = nullptr;
    Octree* fbl = nullptr;
    Octree* fbr = nullptr;

    Octree* btl = nullptr;
    Octree* btr = nullptr;
    Octree* bbl = nullptr;
    Octree* bbr = nullptr;

    Octree* parent = nullptr;

    OctreeNode* node;
    Edge* cubeEdges;
    static const int maxElements = 8;
    float width, height, depth;
    Vector4D start;
    int numData = 0;
    bool hasChildren = false;
};


#endif //TETRAHEDRAL_MESH_OCTREE_H
