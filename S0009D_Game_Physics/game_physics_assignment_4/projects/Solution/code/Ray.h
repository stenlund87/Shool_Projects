//
// Created by ponste-5 on 11/8/17.
//

#ifndef GSCEPT_LAB_ENV_RAY_H
#define GSCEPT_LAB_ENV_RAY_H
#include "Plane.h"
#include "MeshResource.h"

#define GetMax(x, y) ((x) > (y) ? (x) : (y))
#define GetMin(x, y) ((x) < (y) ? (x) : (y))

class Ray
{
    public:
        //Default constructor
        Ray();

        /*Constructor that sets the ray start position
         * @param Vector4D s, start position
         * */
        Ray(Vector4D s, Vector4D d);

        /* Method that check at what point does the ray intersect the plane
         * @param plane, the plane which to check
         * @return Vector4D, point of intersection
         * */
        Vector4D Intersect(Plane plane);

        bool PointInside(Plane plane, Vector4D intersect);

        bool BoundingBoxIntersect(AABB box, Vector4D& global);

//    private:
        Vector4D start;
        Vector4D direction;
        float lenght;

};


#endif //GSCEPT_LAB_ENV_RAY_H
