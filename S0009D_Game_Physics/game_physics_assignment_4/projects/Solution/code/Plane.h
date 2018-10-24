//
// Created by ponste-5 on 11/8/17.
//

#ifndef GSCEPT_LAB_ENV_PLANE_H
#define GSCEPT_LAB_ENV_PLANE_H


#include <vm_mathlib.h>

class Plane
{
    public:
        //Default contructor
        Plane();

        /*Constructor for setting the planes height and width
         * @param Vector4D norm, the planes normal
         * */
        Plane(Vector4D norm);


        float distance, quadWidth;
        Vector4D normal;
        Vector4D center;
};


#endif //GSCEPT_LAB_ENV_PLANE_H
