#include "Animation.h"

#include <fcntl.h>

#include <zconf.h>




Animation::Animation()
{
    clip = nullptr;
}

bool Animation::SetupNax3(const char *filename)
{

    struct stat st;
    stat(filename, &st);
    this->fileSize = st.st_size;

    int fd = open(filename,O_RDONLY);

    if(fd == -1)
    {
        perror("Could not open file!");
        return false;
    }

    //Load file into memory
    void* ptr = mmap(NULL,  this->fileSize, PROT_READ, MAP_PRIVATE, fd,0);
    this->beginning  =  ptr;

    if(ptr == MAP_FAILED)
    {
        perror("Something is wrongk!");
    }

    //Assing content in ptr to naxHead
    Nax3Head* naxHead = (Nax3Head*) ptr;

    //Move the pointer forward
    ptr += sizeof(Nax3Head);

    //Check if the magic is the same type as NA01
    if(naxHead->magic != 'NA01')
    {
        perror("WE GOT NOTHING MAN!");
        return false;
    }

    //Check if the head has any clips
    if(naxHead->numClips > 0)
    {
        this->keys = new Key[naxHead->numKeys];
        this->clip = new Nax3Clip[naxHead->numClips];
        //std::cout << naxHead->numClips << std::endl;

        this->animationslist = new Nax3Group[naxHead->numClips];
        size_t numClips = size_t(naxHead->numClips);

        for(int clipIndex = 0; clipIndex < numClips; clipIndex++)
        {
            Nax3Clip* naxClip = (Nax3Clip*)ptr;
            ptr += sizeof(Nax3Clip);

            Nax3Group Clip;
            Clip.clip = *naxClip;
            Clip.curvelist = new Nax3Curve[naxClip->numCurves];

            for(int eventIndex = 0; eventIndex < naxClip->numEvents; eventIndex++)
            {
                ptr += sizeof(Nax3AnimEvent);
            }

            for(int curveIndex = 0; curveIndex < naxClip->numCurves; curveIndex++)
            {
                Nax3Curve* naxCurve = (Nax3Curve*)ptr;
                ptr += sizeof(Nax3Curve);;
                Clip.curvelist[curveIndex] = *naxCurve;
            }
            animationslist[clipIndex] = Clip;
        }
        for(int i = 0; i < naxHead->numKeys; i++)
        {
            Key* key = (Key*)ptr;
            ptr += sizeof(Key);
            this->keys[i] = *key;
        }
    }
    close(fd);
    return true;
}

void Animation::SetupAnimation(int index, Skeleton* skeleton, float dt)
{
    Nax3Clip clip = this->animationslist[index].clip;
    time = time + dt;

    if (time > clip.keyDuration)
    {
        frame++;
        previousKey++;
        time = 0.0f;
    }
    if(frame >= clip.numKeys)
    {
        frame = 0;
    }
    previousKey = frame > 0 ? frame -1 : clip.numKeys-1;

   Key currentTranslationKey;
   Key currentRotationKey;

   Key nextTranslationKey;
   Key nextRotationKey;

    skeleton->tempJoints = skeleton->joints;

    float deltaFrame = this->time/clip.keyDuration;

    for(int i = 0; i < skeleton->joints.size(); i++)
    {
        int key  = this->animationslist[index].curvelist[i*4].firstKeyIndex + previousKey * clip.keyStride;
        int nextKey = this->animationslist[index].curvelist[i*4].firstKeyIndex + clip.keyStride*frame;

        currentTranslationKey = this->keys[key];
        currentRotationKey = this->keys[key + 1];

        nextTranslationKey = this->keys[nextKey];
        nextRotationKey = this->keys[nextKey + 1];

        Vector4D currentTranslation(currentTranslationKey.x, currentTranslationKey.y, currentTranslationKey.z, 1);
        Vector4D currentRotation(currentRotationKey.x, currentRotationKey.y, currentRotationKey.z, currentRotationKey.w);

        Vector4D nextTranslation(nextTranslationKey.x, nextTranslationKey.y, nextTranslationKey.z,1);
        Vector4D nextRotation(nextRotationKey.x, nextRotationKey.y, nextRotationKey.z, nextRotationKey.w);


        Vector4D translation = currentTranslation.Lerp(currentTranslation, nextTranslation, deltaFrame);
        Vector4D rotation = currentRotation.SlerpQuaternion(currentRotation, nextRotation, deltaFrame);

        Matrix4D rotationMatrix;

        rotationMatrix.Quaternion(rotation);
        rotationMatrix = rotationMatrix.Transpose();
        rotationMatrix.Set_Position(translation);
        skeleton->tempJoints[i].transformMatrix = rotationMatrix;
    }

//    skeleton->DrawAnimations();
}

