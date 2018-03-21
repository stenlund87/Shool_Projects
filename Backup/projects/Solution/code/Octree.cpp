#include "Octree.h"

/*!Default Constructor */
Octree::Octree()
{
    node = nullptr;
}

Octree::Octree(float x, float y, float z,Octree* p)
{
    start = Vector4D(x,y,z);
    node = nullptr;
    parent = p;
    numData = 0;

}

Octree::Octree(MeshResource& mesh)
{

}

Octree::Octree(AABB &box, Vertex* buff, std::vector<Edge*>& e, std::vector<Face*>& f , int numV, MeshResource* mesh)
{
    std::cout << f.size() << std::endl;
    int numSplits = 0;
    hasChildren = true;
    width = fabs(box.min[0]) + fabs(box.max[0]);
    height = fabs(box.min[1]) + fabs(box.max[1]);
    depth = fabs(box.min[2]) + fabs(box.max[2]);
//    width = 5.0f;
//    height = 5.0f;
//    depth = 5.0f;
    start = box.min;
    printf("width: %f\n", width);
    printf("height: %f\n", height);
    printf("depth: %f\n", depth);
    node = new OctreeNode();
    numData++;
    std::vector<Vertex>vertices;
    std::vector<int>iBuff;

    Vertex test = buff[0];
    for(int  i = 0; i < numV; i++)
    {
        vertices.push_back(buff[i]);
        InsertVertex(buff[i],numV,numSplits);
    }
    for(int j = 0; j < e.size(); j++)
    {
        FindAndInsert(e[j]->start, e[j]);
        FindAndInsert(e[j]->end, e[j]);

    }
    for(int k = 0; k < f.size(); k++)
    {
        FindAndInsert(f[k]->edge->start, f[k]);
        FindAndInsert(f[k]->edge->next->start, f[k]);
        FindAndInsert(f[k]->edge->next->next->start, f[k]);


    }
    for(int i = 0; i < mesh->sizeOfBuffer; i++)
    {
        iBuff.push_back(mesh->indiceBuffer[i]);
    }
    Cleanup();
    CalculateEdgeVertex();
    CalculateFaceVertex();
//    FixBuffer(vertices,iBuff);
//    InitiateTetrahedra(vertices, iBuff);
    delete[] mesh->verticeBuffer;
    delete[] mesh->indiceBuffer;

    mesh->verticeBuffer = new Vertex[vertices.size()];
    mesh->indiceBuffer = new int[iBuff.size()];

    for(int i = 0; i < vertices.size(); i++)
    {
        mesh->verticeBuffer[i] = vertices[i];
    }

    for(int i = 0; i < iBuff.size(); i++)
    {
        mesh->indiceBuffer[i] = iBuff[i];
    }


    mesh->sizeOfBuffer = iBuff.size();
    mesh->num = vertices.size();
    mesh->SetBO();
//    printf("%i\n", numSplits);




//    printf("%i\n", numV);
//    printf("%i\n", e.size());
//    Cleanup();

}

Octree::~Octree()
{
    for(int i = 0; i < maxElements; i++)
    {
        delete node;
    }
}

/*!Method to set witdth and height for the tree*/
void Octree::SetuDimensions(float w, float h, float d)
{
    width = w;
    height = h;
    depth = d;


    cubeEdges = new Edge[12];

    cubeEdges[0].start = start;
    cubeEdges[0].end = Vector4D(start[0], start[1] + height, start[2]);

    cubeEdges[1].start = Vector4D(start[0], start[1] + height, start[2]);
    cubeEdges[1].end = Vector4D(start[0] + width, start[1] + height, start[2]);

    cubeEdges[2].start = Vector4D(start[0] + width, start[1] + height, start[2]);
    cubeEdges[2].end = Vector4D(start[0]+ width, start[1], start[2]);

    cubeEdges[3].start = Vector4D(start[0]+ width, start[1], start[2]);
    cubeEdges[3].end = start;

    cubeEdges[4].start = Vector4D(start[0], start[1], start[2] + depth);
    cubeEdges[4].end = Vector4D(start[0], start[1] + height, start[2] + depth);

    cubeEdges[5].start = Vector4D(start[0], start[1] + height, start[2] + depth);
    cubeEdges[5].end = Vector4D(start[0] + width, start[1] + height, start[2] + depth);

    cubeEdges[6].start = Vector4D(start[0] + width, start[1] + height, start[2] + depth);
    cubeEdges[6].end = Vector4D(start[0]+ width, start[1], start[2] + depth);

    cubeEdges[7].start = Vector4D(start[0]+ width, start[1], start[2] + depth);
    cubeEdges[7].end =  Vector4D(start[0], start[1], start[2] + depth);

    cubeEdges[8].start = start;
    cubeEdges[8].end = Vector4D(start[0], start[1], start[2]+depth);

    cubeEdges[9].start = Vector4D(start[0], start[1] + height, start[2]);
    cubeEdges[9].end = Vector4D(start[0], start[1] + height, start[2]+depth);

    cubeEdges[10].start = Vector4D(start[0] + width, start[1] + height, start[2]);
    cubeEdges[10].end = Vector4D(start[0] + width, start[1] + height, start[2]+ depth);

    cubeEdges[11].start = Vector4D(start[0]+ width, start[1], start[2]);
    cubeEdges[11].end = Vector4D(start[0]+ width, start[1], start[2]+depth);
}

/*!Split the tree to smaller trees*/
void Octree::Split(Octree* p)
{
    float w = width * 0.5f;
    float h = height * 0.5f;
    float d = depth * 0.5f;

    ftl = new Octree(start[0], start[1] + h, start[2] + d, p); //<< Front top-left
    ftr = new Octree(start[0] + w, start[1] + h, start[2] + d, p); //<< Front top-right
    fbl = new Octree(start[0], start[1], start[2] + d, p); //<< Front bottom-left
    fbr = new Octree(start[0] + w, start[1], start[2] + d, p); //<< Front bottom-right

    btl = new Octree(start[0], start[1] + h, start[2], p); //<< Back top-left
    btr = new Octree(start[0] + w, start[1] + h, start[2], p); //<< Back top-right
    bbl = new Octree(start[0], start[1], start[2], p); //<< Back bottom-left
    bbr = new Octree(start[0] + w, start[1], start[2], p); //<< Back bottom-right

    ftl->SetuDimensions(w,h,d);
    ftr->SetuDimensions(w,h,d);
    fbl->SetuDimensions(w,h,d);
    fbr->SetuDimensions(w,h,d);
    btl->SetuDimensions(w,h,d);
    btr->SetuDimensions(w,h,d);
    bbl->SetuDimensions(w,h,d);
    bbr->SetuDimensions(w,h,d);

    hasChildren = true;

//    if(parent != nullptr)
//    {
//        Vertex temp = node->data;
//        node = new OctreeNode();
//        InsertVertex(temp,0,0);
//    }

}

/*!Insert a new element to the tree*/
/*!
@param element, OctreeElement to insert in the tree
*/
bool Octree::InsertVertex(Vertex& v,const int& numVert, const int& numSplits)
{
    int& y = const_cast<int&>(numVert);
    int& s = const_cast<int&>(numSplits);


    // Check if the child that we wanna insert is within the tree boundary
    if (v.pos[0] < start[0] || v.pos[0] > width +  start[0] ||
        v.pos[1] < start[1] || v.pos[1] > height + start[1] ||
        v.pos[2] < start[2] || v.pos[2] > depth +  start[2] )
        return false;

    //If the child doesn't have any data we insert
    if(numData < 1)
    {
        node = new OctreeNode(v);
        this->numData++;
        s++;
        return true;
    }

    //Here we want to split the tree
    else if(ftl == nullptr)
    {
        Split(this);
    }

    if(ftl->InsertVertex(v, y, s)) return true;
    if(ftr->InsertVertex(v, y, s)) return true;
    if(fbl->InsertVertex(v, y, s)) return true;
    if(fbr->InsertVertex(v, y, s)) return true;

    if(btl->InsertVertex(v, y, s)) return true;
    if(btr->InsertVertex(v, y, s)) return true;
    if(bbl->InsertVertex(v, y, s)) return true;
    if(bbr->InsertVertex(v, y, s)) return true;

    return false;
}

/*!Find an element in the tree */
void Octree::FindElement(Vertex v)
{
    if(numData == 0) return;

    float x = v.pos[0];
    float y = v.pos[1];
    float z = v.pos[2];
    // Checks if the search area overlaps the tree
    if ( x > start[0] + width  || x + width < start[0]  ||
         y > start[1] + height || y + height < start[1] ||
         z > start[2] + depth  || z + depth < start[2]   )
        return;

    if (numData !=0)
    {
        // If the node is withing the search area we insert that node to the output
        if (node->data.pos[0] <= x + width  && node->data.pos[0] >= x &&
            node->data.pos[1] <= y + height && node->data.pos[1] >= y &&
            node->data.pos[2] <= z + depth  && node->data.pos[2] >= z )
            if(v == node->data)
            return;

    }
    if (ftl == nullptr) return;
    //Recursive calls to get all values in the search area
    ftl->FindElement(v);
    ftr->FindElement(v);
    fbl->FindElement(v);
    fbr->FindElement(v);
               
    btl->FindElement(v);
    btr->FindElement(v);
    bbl->FindElement(v);
    bbr->FindElement(v);

}

bool Octree::FindAndInsert(Vector4D v, Edge* e)
{
    if (numData == 0) return false;

    if(node->data.pos[0] == 100)
    {
        goto insertion;
    }
    // Check if the child that we wanna insert is within the tree boundary
    if (v[0] < start[0] || v[0] > width +  start[0] ||
        v[1] < start[1] || v[1] > height + start[1] ||
        v[2] < start[2] || v[2] > depth +  start[2] )
        return false;

    if (numData != 0)
    {
        // If the node is withing the search area we insert that node to the output
        if (node->data.pos[0] <= v[0] + width  && node->data.pos[0] >= v[0] &&
            node->data.pos[1] <= v[1] + height && node->data.pos[1] >= v[1] &&
            node->data.pos[2] <= v[2] + depth  && node->data.pos[2] >= v[2])
            if (v[0] == node->data.pos[0] && v[1] == node->data.pos[1] && v[2] == node->data.pos[2])
            {
                node->edge[node->numEdges] = e;
                node->numEdges++;
                return true;

            }

    }
    insertion:
    if (ftl == nullptr) return false;
    //Recursive calls to get all values in the search area
    if(ftl->FindAndInsert(v, e)) return true;
    if(ftr->FindAndInsert(v, e)) return true;
    if(fbl->FindAndInsert(v, e)) return true;
    if(fbr->FindAndInsert(v, e)) return true;

    if(btl->FindAndInsert(v, e)) return true;
    if(btr->FindAndInsert(v, e)) return true;
    if(bbl->FindAndInsert(v, e)) return true;
    if(bbr->FindAndInsert(v, e)) return true;

}

bool Octree::FindAndInsert(Vector4D v, Face *f)
{

    if (numData == 0) return false;


    if(node->data.pos[0] == 100)
    {
        goto insertion;
    }
    // Check if the child that we wanna insert is within the tree boundary
    if (v[0] < start[0] || v[0] > width +  start[0] ||
        v[1] < start[1] || v[1] > height + start[1] ||
        v[2] < start[2] || v[2] > depth +  start[2] )
        return false;

    if (numData != 0)
    {
        // If the node is withing the search area we insert that node to the output
        if (node->data.pos[0] <= v[0] + width  && node->data.pos[0] >= v[0] &&
            node->data.pos[1] <= v[1] + height && node->data.pos[1] >= v[1] &&
            node->data.pos[2] <= v[2] + depth  && node->data.pos[2] >= v[2])
            if (v[0] == node->data.pos[0] && v[1] == node->data.pos[1] && v[2] == node->data.pos[2])
            {
                node->face[node->numFaces] = f;
                node->numFaces++;
                return true;

            }

    }
    insertion:
    if (ftl == nullptr) return false;

    //Recursive calls to get all values in the search area
    if(ftl->FindAndInsert(v, f)) return true;
    if(ftr->FindAndInsert(v, f)) return true;
    if(fbl->FindAndInsert(v, f)) return true;
    if(fbr->FindAndInsert(v, f)) return true;

    if(btl->FindAndInsert(v, f)) return true;
    if(btr->FindAndInsert(v, f)) return true;
    if(bbl->FindAndInsert(v, f)) return true;
    if(bbr->FindAndInsert(v, f)) return true;
}

void Octree::DrawTree()
{
    glBegin(GL_LINES);

    glVertex3f(start[0],start[1], start[2]);
    glVertex3f(start[0],start[1] + height, start[2]);


    glVertex3f(start[0],start[1] + height, start[2]);
    glVertex3f(start[0] + width,start[1] + height, start[2]);



    glVertex3f(start[0] + width,start[1], start[2]);
    glVertex3f(start[0],start[1], start[2]);


    glVertex3f(start[0] + width, start[1], start[2]);
    glVertex3f(start[0] + width,start[1] + height, start[2]);

    glVertex3f(start[0],start[1], start[2] + depth);
    glVertex3f(start[0],start[1] + height, start[2] + depth);


    glVertex3f(start[0],start[1] + height, start[2] + depth);
    glVertex3f(start[0] + width,start[1] + height, start[2] + depth);

    glVertex3f(start[0] + width,start[1], start[2] + depth);
    glVertex3f(start[0],start[1], start[2] + depth);

    glVertex3f(start[0] + width,start[1], start[2] + depth);
    glVertex3f(start[0] + width,start[1] + height, start[2] + depth);

    glVertex3f(start[0],start[1], start[2]);
    glVertex3f(start[0],start[1], start[2] + depth);

    glVertex3f(start[0],start[1] + height, start[2]);
    glVertex3f(start[0],start[1] + height, start[2] + depth);

    glVertex3f(start[0] + width,start[1], start[2]);
    glVertex3f(start[0] + width,start[1], start[2] + depth);


    glVertex3f(start[0] + width,start[1] + height, start[2]);
    glVertex3f(start[0] + width,start[1] + height, start[2] + depth);

//    glVertex3f(start[0],start[1], start[2]);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//    glVertex3f(start[0],start[1] + height, start[2]);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//    glVertex3f(start[0] + width,start[1] + height, start[2]);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//    glVertex3f(start[0] + width, start[1], start[2]);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//    glVertex3f(start[0],start[1], start[2] + depth);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//    glVertex3f(start[0],start[1] + height, start[2] + depth);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//    glVertex3f(start[0] + width,start[1], start[2] + depth);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//    glVertex3f(start[0] + width,start[1] + height, start[2] + depth);
//    glVertex3f(mid[0], mid[1], mid[2]);
//
//
//    glVertex3f(start[0] + width,start[1] + height, start[2]);
//    glVertex3f(mid[0], mid[1], mid[2]);


    glEnd();


    if(ftl != nullptr) ftl->DrawTree();
    if(ftr != nullptr) ftr->DrawTree();
    if(fbl != nullptr) fbl->DrawTree();
    if(fbr != nullptr) fbr->DrawTree();

    if(btl != nullptr) btl->DrawTree();
    if(btr != nullptr) btr->DrawTree();
    if(bbl != nullptr) bbl->DrawTree();
    if(bbr != nullptr) bbr->DrawTree();

    std::vector<Vector4D> p;


    DrawPoints(p);


    glPointSize(10.0f);
    glBegin(GL_POINTS);
    for(int i = 0; i < p.size(); i++)
    {
        glVertex3f(p[i].coordinates[0],p[i].coordinates[1],p[i].coordinates[2]);
    }

    glEnd();


}

void Octree::InitiateTetrahedra(std::vector<Vertex>& vBuff, std::vector<int>& iBuff)
{

    if(!hasChildren)
    {
        int indice = vBuff.size();

        vBuff.push_back(Vertex(start));
        vBuff.push_back(Vertex(Vector4D(start[0], start[1] + height, start[2])));
        vBuff.push_back(Vertex(Vector4D(start[0] + width, start[1] + height, start[2])));
        vBuff.push_back(Vertex(Vector4D(start[0] + width, start[1], start[2])));
        vBuff.push_back(Vertex(Vector4D(start[0], start[1] + height, start[2] + depth)));
        vBuff.push_back(Vertex(Vector4D(start[0] + width, start[1] + height, start[2] + depth)));
        vBuff.push_back(Vertex(Vector4D(start[0], start[1], start[2] + depth)));
        vBuff.push_back(Vertex(Vector4D(start[0] + width, start[1], start[2] + depth)));

//        vBuff.push_back(Vertex(Vector4D(start[0] + width*0.5f, start[1] + height*0.5f , start[2] + depth*0.5f))); //mid point

//        First Tetrahedron
        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 4);

        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 4);

        iBuff.push_back(indice + 4);
        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 6);

        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 5);
//
        //Second Tetrahedron
        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 3);

        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 2);
        iBuff.push_back(indice + 5);

        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 3);
        iBuff.push_back(indice + 2);

        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 2);
        iBuff.push_back(indice + 3);

        //Third Tetrahedron
        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 3);
        iBuff.push_back(indice + 0);

        iBuff.push_back(indice + 0);
        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 3);

        iBuff.push_back(indice + 3);
        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 6);

        iBuff.push_back(indice + 0);
        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 1);


        //Fourth Tetrahedron
        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 7);

        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 3);
        iBuff.push_back(indice + 7);

        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 3);
        iBuff.push_back(indice + 7);

        iBuff.push_back(indice + 3);
        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 5);

        //Fifth Tetrahedron
        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 6);

        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 3);

        iBuff.push_back(indice + 5);
        iBuff.push_back(indice + 6);
        iBuff.push_back(indice + 3);

        iBuff.push_back(indice + 1);
        iBuff.push_back(indice + 3);
        iBuff.push_back(indice + 6);


    }
    else
    {
        if(ftl != nullptr) ftl->InitiateTetrahedra(vBuff,iBuff);
        if(ftr != nullptr) ftr->InitiateTetrahedra(vBuff,iBuff);
        if(fbl != nullptr) fbl->InitiateTetrahedra(vBuff,iBuff);
        if(fbr != nullptr) fbr->InitiateTetrahedra(vBuff,iBuff);
        if(btl != nullptr) btl->InitiateTetrahedra(vBuff,iBuff);
        if(btr != nullptr) btr->InitiateTetrahedra(vBuff,iBuff);
        if(bbl != nullptr) bbl->InitiateTetrahedra(vBuff,iBuff);
        if(bbr != nullptr) bbr->InitiateTetrahedra(vBuff,iBuff);

    }


}


//Since we push the data as far down the tree we can, we can set some children to nullptr so ease the search
bool Octree::Cleanup()
{
    if(ftl != nullptr && ftl->Cleanup()) ftl = nullptr;
    if(ftr != nullptr && ftr->Cleanup()) ftr = nullptr;
    if(fbl != nullptr && fbl->Cleanup()) fbl = nullptr;
    if(fbr != nullptr && fbr->Cleanup()) fbr = nullptr;

    if(btl != nullptr && btl->Cleanup()) btl = nullptr;
    if(btr != nullptr && btr->Cleanup()) btr = nullptr;
    if(bbl != nullptr && bbl->Cleanup()) bbl = nullptr;
    if(bbr != nullptr && bbr->Cleanup()) bbr = nullptr;

    if(numData == 0) return true;

    return false;

}

void Octree::CalculateEdgeVertex()
{

    if(ftl != nullptr) ftl->CalculateEdgeVertex();
    if(ftr != nullptr) ftr->CalculateEdgeVertex();
    if(fbl != nullptr) fbl->CalculateEdgeVertex();
    if(fbr != nullptr) fbr->CalculateEdgeVertex();

    if(btl != nullptr) btl->CalculateEdgeVertex();
    if(btr != nullptr) btr->CalculateEdgeVertex();
    if(bbl != nullptr) bbl->CalculateEdgeVertex();
    if(bbr != nullptr) bbr->CalculateEdgeVertex();

    if(parent != nullptr && node != nullptr)
    {
        Vertex point;
        Vertex AB;
        node->edgePoint = new Vertex[node->numEdges];
        for(int i = 0; i < node->numEdges; i++)
        {
            Vertex A = node->edge[i]->start;
            Vertex B = node->edge[i]->end;

            AB = (A + B)*0.5f;
            point = AB;

            if(AB[0] < start[0]) point[0] = start[0];
            else if(AB[0] > start[0] + width) point[0] = start[0] + width;

            if(AB[1] < start[1]) point[1] = start[1];
            else if(AB[1] > start[1] + width) point[1] = start[1] + height;

            if(AB[2] < start[2]) point[2] = start[2];
            else if(AB[2] > start[2] + depth) point[2] = start[2] + depth;
            node->edgePoint[i] = point;
        }
    }

}

void Octree::CalculateFaceVertex()
{
    if(ftl != nullptr) ftl->CalculateFaceVertex();
    if(ftr != nullptr) ftr->CalculateFaceVertex();
    if(fbl != nullptr) fbl->CalculateFaceVertex();
    if(fbr != nullptr) fbr->CalculateFaceVertex();

    if(btl != nullptr) btl->CalculateFaceVertex();
    if(btr != nullptr) btr->CalculateFaceVertex();
    if(bbl != nullptr) bbl->CalculateFaceVertex();
    if(bbr != nullptr) bbr->CalculateFaceVertex();

    if(parent != nullptr && node != nullptr)
    {
        std::vector<Vertex> intersectPoints;
       for(int i = 1; i < node->numEdges; i++)
       {
           Vector4D A = node->data.pos;
           Vector4D B = node->edgePoint[i-1].pos;
           Vector4D C = node->edgePoint[i].pos;;

           Vector4D AB = B - A;
           Vector4D AC = C - A;

           Vector4D normal = AB.CrossProduct(AC);

           for(int j = 0; j < 12; j++)
           {
               Vertex fp;
               int numTrue = 0;
               bool x = false, y = false, z = false;
               Vector4D dir = cubeEdges[j].end - cubeEdges[j].start;
               float det = dir*normal;
               if(det == 0) continue;
               float scalar = (A - cubeEdges[j].start)*normal/det;
               if(scalar < 0) continue;
               fp = dir * scalar + cubeEdges[j].start;

               if(fp[0] < start[0])
               {
                   fp[0] = start[0];
                   x = true;
               }
               else if(fp[0] > start[0] + width)
               {
                   fp[0] = start[0] + width;
                   x = true;
               }
               else if(fp[0] == start[0] ) x = true;

               if(fp[1] < start[1])
               {
                   fp[1] = start[1];
                   y = true;
               }
               else if(fp[1] > start[1] + height)
               {
                   fp[1] = start[1] + height;
                   y = true;
               }
               else if(fp[1] == start[1] || fp[1] == start[1] + height)
               {
                   y = true;
               }

               if(fp[2] < start[2])
               {
                   fp[2] = start[2];
                   z = true;
               }
               else if(fp[2] > start[2] + depth)
               {
                   fp[2] = start[2] + depth;
                   z = true;
               }
               else if((fp[2] == start[2]) || (fp[2] == start[2] + depth)) z = true;

               if(x) numTrue++;
               if(y) numTrue++;
               if(z) numTrue++;

               if(numTrue >= 2 && (fp != node->data || fp != node->edgePoint[i-1] || fp != node->edgePoint[i]))
                   intersectPoints.push_back(fp);
           }
       }
        node->facePoint = new Vertex[intersectPoints.size()];
        node->numFaces = intersectPoints.size();
        for(int j = 0; j < intersectPoints.size(); j++)
        {
            node->facePoint[j] = intersectPoints[j];
        }
    }
}

void Octree::FixBuffer(std::vector<Vertex>& vBuff, std::vector<int>& iBuff)
{

    if (ftl != nullptr) ftl->FixBuffer(vBuff, iBuff);
    if (ftr != nullptr) ftr->FixBuffer(vBuff, iBuff);
    if (fbl != nullptr) fbl->FixBuffer(vBuff, iBuff);
    if (fbr != nullptr) fbr->FixBuffer(vBuff, iBuff);

    if (btl != nullptr) btl->FixBuffer(vBuff, iBuff);
    if (btr != nullptr) btr->FixBuffer(vBuff, iBuff);
    if (bbl != nullptr) bbl->FixBuffer(vBuff, iBuff);
    if (bbr != nullptr) bbr->FixBuffer(vBuff, iBuff);

    if(parent != nullptr && node != nullptr)
    {
        std::vector<Vertex> tempBuffer;
        vBuff.push_back(node->data);
        tempBuffer.push_back(node->data);
        int firstVertex = vBuff.size() - 1;
        for(int i = 1; i < node->numEdges; i++)
        {
//            vBuff.push_back(node->edgePoint[i]);
            if(node->facePoint[i].pos[0] == 100) continue;

            tempBuffer.push_back(node->edgePoint[i-1]);
            tempBuffer.push_back(node->edgePoint[i]);
        }
        for(int j = 1; j < node->numFaces; j++)
        {
            if(node->facePoint[j].pos[0] == 100) continue;
            if(node->facePoint[j-1].pos[0] != 100) tempBuffer.push_back(node->facePoint[j-1]);

//            vBuff.push_back(node->facePoint[j]);
            tempBuffer.push_back(node->data);
            tempBuffer.push_back(node->facePoint[j]);

        }
//        for(int k = vBuff.size() - (node->numFaces+node->numEdges); k < vBuff.size(); k++ )
        int index = iBuff.size();
        for(int k = 0; k < tempBuffer.size(); k++ )
        {
            iBuff.push_back(index+k);
//            iBuff.push_back(firstVertex);
//
//            iBuff.push_back(k);
//            iBuff.push_back(k+1);
        }
        for(int i = 0; i < tempBuffer.size(); i++)
        {
            vBuff.push_back(tempBuffer[i]);
        }
    }
//    printf("Hejsan hoppsan\n");

}

void Octree::DrawPoints(std::vector<Vector4D>& points)
{


    if (ftl != nullptr) ftl->DrawPoints(points);
    if (ftr != nullptr) ftr->DrawPoints(points);
    if (fbl != nullptr) fbl->DrawPoints(points);
    if (fbr != nullptr) fbr->DrawPoints(points);

    if (btl != nullptr) btl->DrawPoints(points);
    if (btr != nullptr) btr->DrawPoints(points);
    if (bbl != nullptr) bbl->DrawPoints(points);
    if (bbr != nullptr) bbr->DrawPoints(points);

//    if (node != nullptr && node->edgePoint != nullptr)
//    {
//        points.push_back(node->data.pos);
//        for (int i = 0; i < node->numEdges; i++)
//        {
//            points.push_back(node->edgePoint[i].pos);
//
//        }
//    }
    if (node != nullptr && node->facePoint != nullptr)
    {
        for (int i = 0; i < node->numFaces; i++)
        {
            points.push_back(node->facePoint[i].pos);

        }
    }

}