//
// Created by ponste-5 on 11/8/17.
//

#include "Ray.h"

Ray::Ray()
{
    start = Vector4D(0,0,0);
    direction = Vector4D(0,0,0);
}

Ray::Ray(Vector4D s, Vector4D d)
{
    start = s;
    direction = d;
}

Vector4D Ray::Intersect(Plane plane)
{
    Vector4D point = Vector4D(0,0,0,-1);

    float det = this->direction * plane.normal;
    if (det == 0)
    {
        std::cout << "miss" << std::endl;
        return point;
    }

    float scalar = (plane.center - this->start)*plane.normal / det;
    if (scalar < 0)
    {
        std::cout << "miss" << std::endl;
        return point;
    }

    point = this->direction * scalar + this->start;
    return point;

}

bool Ray::PointInside(Plane plane, Vector4D intersect)
{
    bool xTrue = (plane.center[0] + plane.quadWidth) > intersect[0] && plane.center[0] - plane.quadWidth < intersect[0];
    bool yTrue = (plane.center[1] + plane.quadWidth) > intersect[1] && plane.center[1] - plane.quadWidth < intersect[1];
    return xTrue && yTrue;
}

bool Ray::BoundingBoxIntersect(AABB box, Vector4D& global)
{
    Vector4D tMin = (box.min - this->start)/this->direction;
    Vector4D tMax = (box.max - this->start)/this->direction;

    Vector4D t1,t2;
    for (int i =0 ;i< 3;i++)
    {
        if (tMin[i] <= tMax[i])
        {
            t1[i] = tMin[i];
            t2[i] = tMax[i];
        }
        else
        {
            t2[i] = tMin[i];
            t1[i] = tMax[i];
        }
    }

    float tNear = GetMax(GetMax(t1[0], t1[1]), t1[2]);
    float tFar = GetMin(GetMin(t2[0], t2[1]), t2[2]);

    global = start + direction*tNear;
    return tNear > 0.0 && tNear < tFar;

}

