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

struct SupportPoint
{
    SupportPoint()
    {
        v = Vector4D();
        supA = Vector4D();
        supB = Vector4D();
    }

    Vector4D v;
    Vector4D supA;
    Vector4D supB;
    bool operator==(const SupportPoint &rhs) {return v == rhs.v;}
};

struct Edge
{
    Edge(){};
    Edge(SupportPoint p1, SupportPoint p2)
    {
        points[0] = p1;
        points[1] = p2;
    };
    SupportPoint points[2];
};


struct Triangle
{
    Triangle()
    {
        std::cout << "Fuck this shit" << std::endl;
    }
    Triangle(SupportPoint& a,  SupportPoint& b, SupportPoint& c)
    {
        points[0] = a;
        points[1] = b;
        points[2] = c;

        Vector4D AB = b.v - a.v;
        Vector4D AC = c.v - a.v;
        Vector4D norm = AB.CrossProduct(AC);

        normal = ((b.v-a.v).CrossProduct(c.v-a.v)).Normalize();
    }
    SupportPoint points[3];
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
    Vector4D point;
    float depth;
};

class Collision
{
    public:
        Collision();
        ~Collision();
        bool GJK(MeshResource& shape1, MeshResource& shape2);
    SupportPoint Support(MeshResource& shape1, MeshResource& shape2, Vector4D dir);
        std::set<std::pair<int,int>> LineSweep();
        void CreateLines(std::vector<MeshResource>& objects, int axis);
        std::set<std::pair<int,int>> CheckCollisions(std::vector<MeshResource>& objects);
        bool ContainsOrigin(std::vector<SupportPoint>& s, Vector4D& dir);
        CollisionInfo EPA(MeshResource& shape1, MeshResource& shape2);
        void AddEdge(SupportPoint& A, SupportPoint& B , std::vector<Edge>& edges);
        Vector4D CalculatePoint(Vector4D& P, Vector4D& A, Vector4D& B, Vector4D& C);
        void CalculateImpulse(MeshResource& shape1, MeshResource& shape2, CollisionInfo info, float dt, int integrator);
        std::multiset<Point> lines;
        std::vector<SupportPoint> simplex;

};


#endif //GAME_PHYSICS_ASSIGNMENT_3_COLLISION_H
