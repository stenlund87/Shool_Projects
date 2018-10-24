#ifndef GSCEPT_LAB_ENV_ANIMATION_H
#define GSCEPT_LAB_ENV_ANIMATION_H


#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include "Skeleton.h"

struct Nax3Head
{
    unsigned int magic;
    unsigned int numClips;
    unsigned int numKeys;
};

struct Nax3Clip
{
    unsigned short numCurves;
    unsigned short startIndex;
    unsigned short numKeys;
    unsigned short keyStride;
    unsigned short keyDuration;
    unsigned char preInfinityType;
    unsigned char postInfinityType;
    unsigned short numEvents;
    char name[50];
};

struct Nax3AnimEvent
{
    char name[47];
    char category[15];
    unsigned short keyIndex;
};

struct Nax3Curve
{
    unsigned int firstKeyIndex;
    unsigned char isActive;
    unsigned char isStatic;
    unsigned char curveType;
    unsigned char padding;
    float staticKeyX;
    float staticKeyY;
    float staticKeyZ;
    float staticKeyW;
};
struct Nax3Group
{
    Nax3Clip clip;
    Nax3Curve* curvelist;
};

struct Key
{
    float x, y , z, w;
};


class Animation
{
    public:
        Animation();
        ~Animation()
        {
            munmap(beginning, fileSize);
            delete[] clip;
            delete[] keys;
        };
        bool SetupNax3(const char* filename);
        void SetupAnimation(int index, Skeleton* skeleton, float dt);


        Nax3Clip* clip;
        std::vector<Nax3Curve*> curve;
        Key* keys;
        Nax3Group* animationslist;

        unsigned int frame = 1;
        unsigned int previousKey = 0;
        float time = 0;
        size_t fileSize;
        void* beginning;
};


#endif //GSCEPT_LAB_ENV_ANIMATION_H
