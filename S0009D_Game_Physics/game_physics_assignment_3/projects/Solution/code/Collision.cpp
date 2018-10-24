//
// Created by ponste-5 on 12/7/17.
//

#include "Collision.h"

Collision::Collision()
{
    lines = std::multiset<Point>();
}

Collision::~Collision()
{
    lines.clear();
}

bool Collision::GJK(MeshResource& shape1, MeshResource& shape2)
{
    simplex.clear();
    std::set<Vector4D>::iterator it;
    Vector4D dir(1,0,0);
    Vector4D point = Support(shape1, shape2, dir);
    simplex.push_back(point);
    dir = point *-1.0f;
    while(true)
    {
        Vector4D end = Support(shape1, shape2, dir);
        simplex.push_back(end);

        if((end * dir) < 0)
        {
            return false;
        }
        else
        {
            if(ContainsOrigin(simplex,dir)) //<< Checks if simplex contains origin,if not we change the direction
            {
                return true;
            }
        }
    }
}

bool Collision::ContainsOrigin(std::vector<Vector4D>& s, Vector4D& dir)
{
    Vector4D AO;
    Vector4D AB;
    Vector4D AC;
    Vector4D AD;

    Vector4D ABperp;
    Vector4D ACperp;

    Vector4D ABCperp;
    Vector4D ACDperp;
    Vector4D ADBperp;

    int simplexSize = s.size();
    if (simplexSize == 2) //<< If size of simplex is 2 we only need a new search direction
    {
        dir = ((s[0] - s[1]).CrossProduct(s[1] * -1)).CrossProduct(s[0] - s[1]); //<< Triple product
    }
    else if(simplexSize == 3)//<< If the size is 3 we need to check if it contains origin
    {
        AO = s[2] * -1;
        AB = s[1] - s[2];
        AC = s[0] - s[2];

        ABperp = AC.CrossProduct(AB).CrossProduct(AB);//<< Triple product
        if (AO * ABperp > 0)
        {
            dir = AB.CrossProduct(AO).CrossProduct(AB);//<< Triple product
            s.erase(s.begin());
        }
        else
        {
            ACperp = AB.CrossProduct(AC).CrossProduct(AC); //<< Triple product
            if (AO * ACperp > 0)
            {
                dir = AC.CrossProduct(AO).CrossProduct(AC); //<< Triple product
                s.erase(s.begin()+1);
            }
            else
            {
                ABCperp = AC.CrossProduct(AB);
                if (AO * ABCperp > 0)
                {
                    dir = ABCperp;
                }
                else
                {
                    dir = (ABCperp * -1);
                    Vector4D temp = s[1];
                    s[1] = s[2];
                    s[2] = temp;
                }
            }
        }
    }
    else //<< We have a tetrahedron, its now or never
    {
        AO = s[3] * -1;
        AB = s[2] - s[3];
        AC = s[1] - s[3];
        AD = s[0] - s[3];

        ABCperp = AC.CrossProduct(AB);
        if (AO * ABCperp > 0)
        {
            dir = ABCperp;
            s.erase(s.begin());
        }
        else
        {
            ACDperp = AD.CrossProduct(AC);
            if (AO * ACDperp > 0)
            {
                dir = ACDperp;
                s.erase(s.begin()+2);
            }
            else
            {
                ADBperp = AB.CrossProduct(AD);
                if (AO * ADBperp > 0)
                {
                    dir = ADBperp;
                    s.erase(s.begin()+1);
                    Vector4D temp = s[1];
                    s[1] = s[2];
                    s[2] = temp;

                }
                else //<< Simplex contains origin, we have a collision
                {
                    return true;
                }
            }
        }
    }
    return false;
}

Vector4D Collision::Support(MeshResource& shape1, MeshResource& shape2, Vector4D dir)
{
    Vector4D p1 = shape1.GetFarthestPointInDirection(dir);
    Vector4D p2 = shape2.GetFarthestPointInDirection(dir*-1.0f);
    Vector4D p3 = p1 - p2;
    return p3;
}

std::set<std::pair<int,int>> Collision::LineSweep()
{
    std::set<std::pair<int,int>>intersect;
    std::vector<int>possibleCollisions;

    for(std::multiset<Point>::iterator it = lines.begin(); it!= lines.end(); it++)
    {
        Point point = *it;
        if(point.start)
        {
            point.vectorIndex = possibleCollisions.size();
            possibleCollisions.push_back(point.index);
            for(int i = 1; i < possibleCollisions.size();i++)
            {
                intersect.insert(std::pair<int,int>(possibleCollisions[i-1],possibleCollisions[i]));
            }
        }
        else
        {
            if(possibleCollisions.size() > 0)
            {
                possibleCollisions.erase(possibleCollisions.begin() + point.pair->vectorIndex);
            }

        }
    }

    return intersect;
}

void Collision::CreateLines(std::vector<MeshResource>& objects, int axis)
{
    lines.clear();
    for(int i = 0; i < objects.size(); i++)
    {
        Point start(objects[i].box.min[axis], i,true);
        Point end(objects[i].box.max[axis], i,false);

        start.pair = &end;
        end.pair = &start;
        lines.insert(start);
        lines.insert(end);
    }
}

std::set<std::pair<int,int>> Collision::CheckCollisions(std::vector<MeshResource> &objects)
{
    std::set<std::pair<int,int>> collisions;
    CreateLines(objects,0);
    std::set<std::pair<int,int>> xCollisions = LineSweep();
    CreateLines(objects,1);
    std::set<std::pair<int,int>> yCollisions = LineSweep();
    CreateLines(objects,2);
    std::set<std::pair<int,int>> zCollisions = LineSweep();

    std::set<std::pair<int,int>>::iterator yIter;
    std::set<std::pair<int,int>>::iterator zIter;

    for(std::set<std::pair<int,int>>::iterator it = xCollisions.begin(); it!= xCollisions.end(); it++)
    {
        if(yCollisions.size() > 0)
        {
            yIter = yCollisions.find(*it);
            if(zCollisions.size() > 0)
            {
                zIter = zCollisions.find(*yIter);
                collisions.insert(*zIter);
            }
        }
    }
    return collisions;
}

CollisionInfo Collision::EPA(MeshResource& shape1, MeshResource& shape2)
{
    CollisionInfo info;
    std::vector<Triangle> triangleList;
    std::vector<Edge> edgeList;

    triangleList.push_back(Triangle(simplex[2],simplex[1],simplex[0]));
    triangleList.push_back(Triangle(simplex[3],simplex[2],simplex[0]));
    triangleList.push_back(Triangle(simplex[3],simplex[1],simplex[2]));
    triangleList.push_back(Triangle(simplex[3],simplex[0],simplex[1]));

    Vector4D AO = simplex[3];
    while(true)
    {
        float threshold = INFINITY;
        int index = 0;
        float dot = 0;

        for (int i = 0; i < triangleList.size(); i++)
        {
            dot = fabs(triangleList[i].normal * triangleList[i].points[1]);
            if(dot < threshold)
            {
                threshold = dot;
                index = i;
            }
        }
        Vector4D support = Support(shape1, shape2,triangleList[index].normal);
        if((triangleList[index].normal * support)-threshold < 0.0001f)
        {
            info.normal = triangleList[index].normal * -1.0f;
            info.depth = (triangleList[index].normal * triangleList[index].points[0])*0.5;
            return info;
        }


        for(int i = 0; i < triangleList.size(); i++)
        {
            if (triangleList[i].normal * (support - triangleList[i].points[0]) > 0)
            {
                AddEdge(triangleList[i].points[0], triangleList[i].points[1], edgeList);
                AddEdge(triangleList[i].points[1], triangleList[i].points[2], edgeList);
                AddEdge(triangleList[i].points[2], triangleList[i].points[0], edgeList);
                triangleList.erase(triangleList.begin() + i);
                continue;
            }
        }

        for (int j = 0; j < edgeList.size(); j++)
        {
            Triangle t(edgeList[j].points[0], support,edgeList[j].points[1]);
            triangleList.push_back(Triangle(edgeList[j].points[0], edgeList[j].points[1],support));
        }
        edgeList.clear();
    }
}

void Collision::AddEdge(Vector4D& A, Vector4D& B , std::vector<Edge>& edges)
{
    for(int i = 0; i < edges.size(); i++)
    {
        if(edges[i].points[0] == B && edges[i].points[1] == A)
        {
            edges.erase(edges.begin() + i);
            return;
        }
    }
    edges.push_back(Edge(A,B));
}


