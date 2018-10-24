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
    SupportPoint point = Support(shape1, shape2, dir);
    simplex.push_back(point);
    dir = point.v *-1.0f;
    while(true)
    {
        SupportPoint end = Support(shape1, shape2, dir);
        simplex.push_back(end);

        if((end.v * dir) < 0)
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

bool Collision::ContainsOrigin(std::vector<SupportPoint>& s, Vector4D& dir)
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
        dir = ((s[0].v - s[1].v).CrossProduct(s[1].v * -1)).CrossProduct(s[0].v - s[1].v); //<< Triple product
    }
    else if(simplexSize == 3)//<< If the size is 3 we need to check if it contains origin
    {
        AO = s[2].v * -1;
        AB = s[1].v - s[2].v;
        AC = s[0].v - s[2].v;

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
                    Vector4D temp = s[1].v;
                    s[1].v = s[2].v;
                    s[2].v = temp;
                }
            }
        }
    }
    else //<< We have a tetrahedron, its now or never
    {
        AO = s[3].v * -1;
        AB = s[2].v - s[3].v;
        AC = s[1].v - s[3].v;
        AD = s[0].v - s[3].v;

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
                    Vector4D temp = s[1].v;
                    s[1].v = s[2].v;
                    s[2].v = temp;

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

SupportPoint Collision::Support(MeshResource& shape1, MeshResource& shape2, Vector4D dir)
{
    SupportPoint p;
    p.supA = shape1.GetFarthestPointInDirection(dir);
    p.supB = shape2.GetFarthestPointInDirection(dir*-1.0f);
    p.v = p.supA - p.supB;
    return p;
}

std::set<std::pair<int,int>> Collision::LineSweep()
{
    std::set<std::pair<int,int>>intersect;
    std::vector<int>possibleCollisions = std::vector<int>();

    for(std::multiset<Point>::iterator it = lines.begin(); it!= lines.end(); it++)
    {
        std::vector<int>::iterator intIt = possibleCollisions.begin();
        Point point = *it;
        if(point.start)
        {
            point.vectorIndex = possibleCollisions.size();
            possibleCollisions.push_back(point.index);
            intIt = possibleCollisions.end();
            for(int i = 1; i < possibleCollisions.size();i++)
            {
                intersect.insert(std::pair<int,int>(possibleCollisions[i-1],possibleCollisions[i]));
            }
        }
        else
        {
            if(possibleCollisions.size() > 0)
            {
//                possibleCollisions.erase(possibleCollisions.begin() + point.pair->vectorIndex);
                possibleCollisions.erase(intIt);
                intIt = possibleCollisions.end();
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

    Vector4D AO = simplex[3].v;
    while(true)
    {
        float threshold = INFINITY;
        int index = 0;
        float dot = 0;

        for (int i = 0; i < triangleList.size(); i++)
        {
            dot = fabs(triangleList[i].normal * triangleList[i].points[1].v);
            if(dot < threshold)
            {
                threshold = dot;
                index = i;
            }
        }
        SupportPoint support = Support(shape1, shape2,triangleList[index].normal);

        if((triangleList[index].normal * support.v)-threshold < 0.0001f)
        {
            info.normal = triangleList[index].normal * -1.0f;
            info.depth = (triangleList[index].normal * triangleList[index].points[0].v)*0.5f;
            Vector4D p = info.normal*info.depth;
            Vector4D uvw = CalculatePoint(p, triangleList[index].points[0].v, triangleList[index].points[1].v, triangleList[index].points[2].v);
            info.point = triangleList[index].points[0].supA * uvw[0]+
                         triangleList[index].points[1].supA * uvw[1]+
                         triangleList[index].points[2].supA * uvw[2];
            return info;
        }


        for(int i = 0; i < triangleList.size(); i++)
        {
            if (triangleList[i].normal * (support.v - triangleList[i].points[0].v) > 0)
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
            if((support.v-edgeList[j].points[0].v).CrossProduct(edgeList[j].points[1].v -edgeList[j].points[0].v).Length() < 0.00001)
            {
                support = Support(shape1, shape2,triangleList[index].normal*-1.0f);
            }
            Triangle t(edgeList[j].points[0], support ,edgeList[j].points[1]);
            triangleList.push_back(Triangle(edgeList[j].points[0], edgeList[j].points[1],support));
        }
        edgeList.clear();
    }
}

void Collision::AddEdge(SupportPoint& A, SupportPoint& B , std::vector<Edge>& edges)
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

Vector4D Collision::CalculatePoint(Vector4D& P, Vector4D& A, Vector4D& B, Vector4D& C)
{
    Vector4D v0 = B - A;
    Vector4D v1 = C - A;
    Vector4D v2 = P - A;

    float d00 = v0*v0;
    float d01 = v0*v1;
    float d11 = v1*v1;
    float d20 = v2*v0;
    float d21 = v2*v1;
    float denom = d00 * d11 - d01 * d01;

    float v = (d11 * d20 - d01 * d21)/denom;
    float w = (d00*d21 - d01*d20)/denom;
    float u = 1.0f - v - w;

    Vector4D worldCollision (u, v, w);
    return worldCollision;

}

double Rate(double x, double y)
{
    return x * sqrtf(y);
}

double Euler(double(*func)(double, double), double dt, double h, double acceleration)
{
    double* y = new double[(int)(dt * h)+1];
    y[0] = acceleration;
    y[1] = y[0] + dt * func(h,y[0]);

    for(int i = 2; i < dt*h; i++)
    {
        y[i] = y[i-1] + i * h * func(i*h,y[i-1]);
    }
    return y[(int)(dt*h)];
}

double MidPoint(double(*func)(double, double), double dt, double h, double acceleration)
{

}

double RungeKutta4(double(*func)(double, double), double dt, double vel, double acceleration)
{
    double k1 = dt * func(vel, acceleration),
            k2 = dt * func((vel + dt)*0.5f, (acceleration + k1)*0.5f),
            k3 = dt * func((vel + dt)*0.5f, (acceleration + k2)*0.5f),
            k4 = dt * func(vel + dt, acceleration + k3);
    return (vel + (k1 + k2 + k3 + k4)/6);
}

void Collision::CalculateImpulse(MeshResource& shape1, MeshResource& shape2, CollisionInfo info, float dt, int integrator)
{
    float mass1 = 1.0f/shape1.physics.mass;
    float mass2 = 1.0f/shape2.physics.mass;

    float vel = (shape1.physics.velocity + shape1.physics.spinVector.CrossProduct(info.point - shape1.physics.centerOfMass)
                 - shape2.physics.velocity + shape2.physics.spinVector.CrossProduct(info.point - shape2.physics.centerOfMass)).Length();


    Vector4D normal = info.normal;
    Matrix4D onetensor = shape1.physics.inverseInertiaTensor * shape1.translation;
    Matrix4D twotensor = shape2.physics.inverseInertiaTensor * shape2.translation;

    Vector4D AAngularMomentum = shape1.physics.angularMomentum;
    Vector4D BAngularMomentum = shape2.physics.angularMomentum;

    float div = mass1 + mass2 + normal*(onetensor*((AAngularMomentum.CrossProduct(normal)).CrossProduct(AAngularMomentum)))
    + normal*(twotensor*((BAngularMomentum.CrossProduct(normal)).CrossProduct(BAngularMomentum)));

    float impulse = (vel * -(1.0f + 1.0f))/ div;

    if(info.normal.Length() < 0)
    {
        return;
    }
    float f = info.point[0];
    if(f != f) //<< Check if value if NAN
    {
        return;
    }
    shape1.intersectPoint = (info.point - shape1.physics.centerOfMass).CrossProduct(normal*impulse);
    shape2.intersectPoint = (info.point - shape2.physics.centerOfMass).CrossProduct(normal*impulse*-1.0f);


    switch(integrator)
    {
        case 1:
            shape1.physics.velocity = shape1.physics.velocity + (normal *  Euler(Rate, dt, dt*0.1f, fabs(impulse/shape1.physics.mass)));
            shape2.physics.velocity = shape2.physics.velocity + (normal * Euler(Rate, dt, dt*0.1f, fabs(impulse/shape2.physics.mass)));

            shape1.physics.angularMomentum = shape1.physics.angularMomentum + shape1.intersectPoint;
            shape2.physics.angularMomentum = (shape2.physics.angularMomentum + shape2.intersectPoint);

            break;
        case 2:

            break;
        case 3:
            shape1.physics.velocity = shape1.physics.velocity + (normal * RungeKutta4(Rate, dt, shape2.physics.velocity.Length(), fabs(impulse/shape1.physics.mass)));
            shape2.physics.velocity = shape2.physics.velocity + (normal*-1.0f) * RungeKutta4(Rate, dt, shape2.physics.velocity.Length(),fabs(impulse/shape2.physics.mass));

            shape1.physics.angularMomentum = shape1.physics.angularMomentum + shape1.intersectPoint;
            shape2.physics.angularMomentum = shape2.physics.angularMomentum + shape2.intersectPoint;

            break;

    }
}



