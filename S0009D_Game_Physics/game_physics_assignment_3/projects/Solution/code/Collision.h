//
// Created by ponste-5 on 12/7/17.
//

#ifndef GAME_PHYSICS_ASSIGNMENT_3_COLLISION_H
#define GAME_PHYSICS_ASSIGNMENT_3_COLLISION_H


#include <set>
#include "MeshResource.h"


struct Point
{
    Point(){};
    Point(float b,int i ,bool s)
    {
        p = b;
        index = i;
        start = s;
    };
    bool operator<(const Point &rhs) const
    {
        if(this->p == rhs.p)
        {
            return (this->start);
        }
        return (this->p < rhs.p);
    };

    float p;
    bool start = false;
    int index = -1;
    int vectorIndex = -1;
    Point* pair;
};

struct Edge
{
    Edge(){};
    Edge(Vector4D p1, Vector4D p2)
    {
        points[0] = p1;
        points[1] = p2;
    };
    Vector4D points[2];
};


struct Triangle
{
    Triangle(){};
    Triangle(Vector4D& a,  Vector4D& b, Vector4D& c)
    {
        points[0] = a;
        points[1] = b;
        points[2] = c;
        normal = ((b-a).CrossProduct(c-a)).Normalize();

    };
    Vector4D points[3];
    Vector4D normal;
};

struct CollisionInfo
{
    CollisionInfo()
    {
        normal = Vector4D();
        float depth = 0;
    };
    Vector4D normal;
    float depth;
};

class Collision
{
    public:
        Collision();
        ~Collision();
        bool GJK(MeshResource& shape1, MeshResource& shape2);
        Vector4D Support(MeshResource& shape1, MeshResource& shape2, Vector4D dir);
        std::set<std::pair<int,int>> LineSweep();
        void CreateLines(std::vector<MeshResource>& objects, int axis);
        std::set<std::pair<int,int>> CheckCollisions(std::vector<MeshResource>& objects);
        bool ContainsOrigin(std::vector<Vector4D>& s, Vector4D& dir);
        CollisionInfo EPA(MeshResource& shape1, MeshResource& shape2);
        void AddEdge(Vector4D& A, Vector4D& B , std::vector<Edge>& edges);

        std::multiset<Point> lines;
        std::vector<Vector4D> simplex;

};


#endif //GAME_PHYSICS_ASSIGNMENT_3_COLLISION_H
