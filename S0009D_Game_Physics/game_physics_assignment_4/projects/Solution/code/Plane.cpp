//
// Created by ponste-5 on 11/8/17.
//

#include "Plane.h"

Plane::Plane()
{
    normal = Vector4D(0,0,-1);
    distance = 0.0f;
}

Plane::Plane(Vector4D norm)
{
    normal = norm;
}

