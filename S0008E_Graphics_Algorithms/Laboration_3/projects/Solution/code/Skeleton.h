//
// Created by ponste-5 on 9/5/17.
//

#ifndef GSCEPT_LAB_ENV_SKELETON_H
#define GSCEPT_LAB_ENV_SKELETON_H

#include <vm_mathlib.h>
#include <vector>
#include "ShaderObject.h"


struct Joint
{
    int index;
    int parentIndex;
    Matrix4D transformMatrix;
    const char* name;
    Joint* parent = nullptr;
    float red = 1.0, green = 1.0, blue = 1.0;
};

class Skeleton
{
    public:
        Skeleton();
        ~Skeleton();
        void ReadFromFile(char* filename);
        void CalculateOriginal();
        void Calculate();
        void DrawLimb(const Vector4D& child, const Vector4D& parent);
        void Draw();
        void SetRotation(int axis, int index, float degree);
        void DrawAnimations();
        void ConvertJointsToArray();

        std::vector<Joint> joints;
        std::vector<Joint> tempJoints;
        std::vector<Joint> bindPose;
        float mat[21][16];
        ShaderObject* shader;
        Matrix4D test;

};


#endif //GSCEPT_LAB_ENV_SKELETON_H
