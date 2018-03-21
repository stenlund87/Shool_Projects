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

    point = direction * scalar + this->start;

    std::cout << point.coordinates[0] << " : " << point.coordinates[1] << " : " << point.coordinates[2] << " : " << point.coordinates[3]<< std::endl;

    return point;



//    Vector4D intersectPoint(0,0,0,-1);
////    plane.distance = (this->start-plane.center).Length();
////    std::cout << "Lenght " << plane.distance << std::endl;
//    float denom = plane.normal * this->direction;
//    if(fabs(denom) > 0.0001f)
//    {
//        float t = -((this->start * plane.normal) + plane.distance) / (this->direction * plane.normal);
//        if (t < 0)
//        {
//            std::cout << "Miss" << std::endl;
//            return intersectPoint;
//        }
//        Vector4D temp = this->direction;
//        intersectPoint = this->start + temp * t;
////        intersectPoint.Normalize();
////        intersectPoint[2] = this->direction[2]*t;
//    }
//    std::cout << intersectPoint.coordinates[0] << " : " << intersectPoint.coordinates[1] << " : " << intersectPoint.coordinates[2] << " : " << intersectPoint.coordinates[3]<< std::endl;
//    return intersectPoint;
}

bool Ray::PointInside(Plane plane, Vector4D intersect)
{

    bool xTrue = (plane.center[0] + plane.quadWidth) > intersect[0] && plane.center[0] - plane.quadWidth < intersect[0];
    bool yTrue = (plane.center[1] + plane.quadWidth) > intersect[1] && plane.center[1] - plane.quadWidth < intersect[1];
    return xTrue && yTrue;
}

bool Ray::BoundingBoxIntersect(Plane plane, AABB box, Vector4D point)
{
    return (point[0] > box.min[0]) && (point[0] < box.max[0]) && (point[1] < box.min[1]) && (point[1] > box.max[1]) && (point[2] > box.min[2]) && (point[2] < box.max[2]);
}

