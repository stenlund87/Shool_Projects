

#include "Skeleton.h"
#include <tinyxml2.h>
#include <GL/glew.h>
#include <GL/glut.h>

Skeleton::Skeleton()
{
}

Skeleton::~Skeleton()
{
}

void Skeleton::ReadFromFile(char *filename)
{
    std::vector<Joint> temp;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename);


    //Loop to go through all joints in the xml file
    for(tinyxml2::XMLElement* child = doc.FirstChildElement("Nebula3")->FirstChildElement("Model")->FirstChildElement("CharacterNodes")->FirstChildElement("CharacterNode")->FirstChildElement("Joint");
        child != 0; child = child->NextSiblingElement())
    {
        Joint newJoint;
        newJoint.name = child->ToElement()->Attribute("name");
        std::string ind = child->ToElement()->Attribute("index");
        std::string parent = child->ToElement()->Attribute("parent");

        std::string pos = child->ToElement()->Attribute("position");
        std::string rot = child->ToElement()->Attribute("rotation");
        std::string scale = child->ToElement()->Attribute("scale");

        newJoint.index = stoi(ind);
        newJoint.parentIndex = stoi(parent);

        //Variables needed to split the strings
        size_t stringPosition = 0;
        size_t rotPosition = 0;
        size_t scalePosition = 0;

        std::string delimiter = ",";
        std::string posToken;
        std::string rotToken;
        std::string scaleToken;

        Vector4D positionVector;
        Vector4D rotationVector;
        Vector4D scaleVector;
        int index = 0;

        //Looping through the strings, splitting them and assign the joint value
        while((stringPosition = pos.find(delimiter),(rotPosition = rot.find(delimiter), (scalePosition = scale.find(delimiter))) != std::string::npos))
        {
            posToken = pos.substr(0,stringPosition);
            rotToken = rot.substr(0,rotPosition);
            scaleToken = scale.substr(0,scalePosition);

            //newJoint.position.coordinates[index] = stof(posToken);
            positionVector.coordinates[index] = stof(posToken);
            rotationVector.coordinates[index] = stof(rotToken);
            scaleVector.coordinates[index] = stof(scaleToken);

            pos.erase(0, stringPosition + delimiter.length());
            rot.erase(0, rotPosition + delimiter.length());
            scale.erase(0, scalePosition + delimiter.length());
            index++;
        }
        rotationVector.coordinates[index] = stof(rot);
        scaleVector.coordinates[index] = stof(scale);

        Matrix4D rotationMatrix;

        rotationMatrix.Quaternion(rotationVector);
        rotationMatrix = rotationMatrix.Transpose();
        rotationMatrix.Set_Position(positionVector*0.2);


        newJoint.transformMatrix = rotationMatrix;

        joints.push_back(newJoint);
    }

    //Loop for linking the child joint to the parent joint
    for(int i = 0; i < joints.size(); i++)
    {
        int parent = joints[i].parentIndex;
        if(joints[i].index == 1) //<< Hip is green
        {
            joints[i].red = 0.4;
            joints[i].green = 0.5;
            joints[i].blue = 0.1;
        }
        else if(joints[i].index == 5 || joints[i].index == 9) //<< Shoulders are green
        {
            joints[i].red = 0;
            joints[i].green = 1;
            joints[i].blue = 0;
        }
        else if(joints[i].index == 6 || joints[i].index == 10) //<< Elbows are purple
        {
            joints[i].red = 0.75;
            joints[i].green = 0;
            joints[i].blue = 0.75;
        }
        else if(joints[i].index == 7 || joints[i].index == 11) //<< Hands are pink
        {
            joints[i].red = 1.0;
            joints[i].green = 0.5;
            joints[i].blue = 0.5;
        }
        else if(joints[i].index == 8 || joints[i].index == 12) //<< Shoulderpads are black
        {
            joints[i].red = 0.0;
            joints[i].green = 0.0;
            joints[i].blue = 0;
        }
        else if(joints[i].index == 14 || joints[i].index == 18) //<< Knees are blue
        {
            joints[i].red = 0.0;
            joints[i].green = 0;
            joints[i].blue = 255;
        }
        else if(joints[i].index == 15 || joints[i].index == 19) //<<Feet are green
        {
            joints[i].red = 0.0;
            joints[i].green = 1.0;
            joints[i].blue = 0.0;
        }
        else if(joints[i].index == 16 || joints[i].index == 20) //<<Feet are yellow
        {
            joints[i].red = 1.0;
            joints[i].green = 1.0;
            joints[i].blue = 0.0;
        }


        if(joints[i].parentIndex != -1)
        {
            joints[i].parent = &joints[parent];
            //joints[parent].child = &joints[i];
        }
        else
        {
            // The root will be shown as red
            joints[i].red = 1.0;
            joints[i].green = 0;
            joints[i].blue = 0;
        }
    }
}


void Skeleton::Calculate()
{
    for(int i = 1; i<tempJoints.size(); i++)
    {
        if(tempJoints[i].parentIndex == -1)
        {
            continue;
        }
        else
        {
            tempJoints[i].transformMatrix = tempJoints[tempJoints[i].parentIndex].transformMatrix * tempJoints[i].transformMatrix;

        }
    }

    for(int j = 0; j < tempJoints.size(); j++)
    {
        tempJoints[j].transformMatrix = tempJoints[j].transformMatrix.Transpose();
    }
}

void Convert(float arr[], const Matrix4D &other)
{
    arr[0] = other.matrix[0][0];
    arr[1] = other.matrix[0][1];
    arr[2] = other.matrix[0][2];
    arr[3] = other.matrix[0][3];

    arr[4] = other.matrix[1][0];
    arr[5] = other.matrix[1][1];
    arr[6] = other.matrix[1][2];
    arr[7] = other.matrix[1][3];

    arr[8] = other.matrix[2][0];
    arr[9] = other.matrix[2][1];
    arr[10] = other.matrix[2][2];
    arr[11] = other.matrix[2][3];

    arr[12] = other.matrix[3][0];
    arr[13] = other.matrix[3][1];
    arr[14] = other.matrix[3][2];
    arr[15] = other.matrix[3][3];
}

void Skeleton::Draw()
{
    tempJoints = joints;
    Calculate();

    for(int p = 0; p < tempJoints.size(); p++)
    {
        float arr[16];
        Convert(arr, tempJoints[p].transformMatrix);

        glMatrixMode(GL_PROJECTION);
        glUseProgram(0);
        glPushMatrix();
        glColor3f(tempJoints[p].red, tempJoints[p].green, tempJoints[p].blue);
        glLoadMatrixf(arr);
        glutWireSphere(0.03,10,10);
        glPopMatrix();

        glFlush();

        if(tempJoints[p].parentIndex > 0)
        {
            glLineWidth(1);
            glColor3f(0,0,255);
            glBegin(GL_LINES);
            float cx = arr[12];
            float cy = arr[13];
            float cz = arr[14];

            Convert(arr, tempJoints[tempJoints[p].parentIndex].transformMatrix);

            float px = arr[12];
            float py = arr[13];
            float pz = arr[14];

            glVertex3f(cx,cy,cz);
            glVertex3f(px,py,pz);
            glEnd();
        }
    }
}

void Skeleton::SetRotation(int axxis, int index, float degree)
{
    Matrix4D rotation;
    switch(axxis)
    {
        case 0:
            rotation = rotation.Rotation_X(degree);
            break;
        case 1:
            rotation = rotation.Rotation_Y(degree);
            break;
        case 2:
            rotation = rotation.Rotation_Z(degree);
            break;
    }
    joints[index].transformMatrix = joints[index].transformMatrix * rotation;
}

void Skeleton::DrawAnimations()
{
    Calculate();
    for(int p = 0; p < tempJoints.size(); p++)
    {
        float arr[16];
        Convert(arr, tempJoints[p].transformMatrix);

        glMatrixMode(GL_PROJECTION);
        glUseProgram(0);
        glPushMatrix();
        glColor3f(tempJoints[p].red, tempJoints[p].green, tempJoints[p].blue);
        glLoadMatrixf(arr);
        glutWireSphere(0.01,4,4);
        glPopMatrix();

        glFlush();

        if(tempJoints[p].parentIndex > 0)
        {
            glLineWidth(1);
            glColor3f(0,0,255);
            glBegin(GL_LINES);
            float cx = arr[12];
            float cy = arr[13];
            float cz = arr[14];

            Convert(arr, tempJoints[tempJoints[p].parentIndex].transformMatrix);

            float px = arr[12];
            float py = arr[13];
            float pz = arr[14];

            glVertex3f(cx,cy,cz);
            glVertex3f(px,py,pz);
            glEnd();
        }
    }
}

