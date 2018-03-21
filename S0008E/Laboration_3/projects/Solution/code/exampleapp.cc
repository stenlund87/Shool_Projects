//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "GraphicsNode.h"
#include <iostream>
#include <chrono>


TextureResource tex;
MeshResource* mesh;
ShaderObject bla;
LightNode lightyGonzales;

GraphicsNode test;

Matrix4D camera;
Matrix4D movement;
Matrix4D tempRotX;
Matrix4D tempRotY;
Matrix4D rotation;
Matrix4D finalRot;

Skeleton* skeleton;
Animation* anim;
Skinning* skin;

int animation = 0;

Vector4D pos;

float speedyGonzales = 0;
float flash = 0;
bool mousePressed = false;

bool moveUP, moveDown, moveRight, moveLeft;

int oldX = 0;
int oldY = 0;

using namespace Display;
namespace Example
{

    //------------------------------------------------------------------------------
    /**
    */
    ExampleApp::ExampleApp()
    {
        // empty
    }

    //------------------------------------------------------------------------------
    /**
    */
    ExampleApp::~ExampleApp()
    {
        // empty
    }

    //------------------------------------------------------------------------------
    /**
    */
    bool
    ExampleApp::Open()
    {
        App::Open();
        this->window = new Display::Window;
        window->SetKeyPressFunction([this](int32 key, int32 scanner, int32 action, int32)
        {
            if (action == GLFW_PRESS)
            {
                if (key == GLFW_KEY_W)
                {
                    moveUP = true;
                }
                else if (key == GLFW_KEY_S)
                {
                    moveDown = true;
                }
                else if (key == GLFW_KEY_A)
                {
                    moveLeft = true;
                }
                else if (key == GLFW_KEY_D)
                {
                    moveRight = true;
                }
                else if (key == GLFW_KEY_R)
                {
                    tempRotX = tempRotX.Rotation_X(90.0f);
                    tempRotY = tempRotY.Rotation_Y(90.0f);

                    finalRot = tempRotX*tempRotY;
                }
                else if(key == GLFW_KEY_1){animation = 0; }
                else if(key == GLFW_KEY_2){animation = 1; }
                else if(key == GLFW_KEY_3){animation = 2; }
                else if(key == GLFW_KEY_4){animation = 3; }
                else if(key == GLFW_KEY_5){animation = 4; }
                else if(key == GLFW_KEY_6){animation = 5; }
                else if(key == GLFW_KEY_7){animation = 6; }
                else if(key == GLFW_KEY_8){animation = 7; }
                else if (key == GLFW_KEY_ESCAPE)
                {
                    this->window->Close();
                }
            }
            else if (action == GLFW_RELEASE)
            {
                if (key == GLFW_KEY_W)
                {
                    moveUP = false;
                }
                else if (key == GLFW_KEY_S)
                {
                    moveDown = false;
                }
                else if (key == GLFW_KEY_A)
                {
                    moveLeft = false;
                }
                else if (key == GLFW_KEY_D)
                {
                    moveRight = false;
                }
            }



        });

        window->SetMousePressFunction([this](int32 left, int32 pressed, int32 modifier)
          {
              if (left == GLFW_MOUSE_BUTTON_LEFT && pressed == GLFW_PRESS)
              {
                  mousePressed = true;
              }
              else if (left == GLFW_MOUSE_BUTTON_LEFT && pressed == GLFW_RELEASE)
              {
                  mousePressed = false;
              }
          }
        );


        window->SetMouseMoveFunction([this](float64 mouseXPos, float64 mouseYPos)
         {
             float deltaX = mouseXPos - oldX;
             float deltaY = mouseYPos - oldY;
             if (mousePressed)
             {
                 tempRotX = tempRotX.Rotation_X(-deltaY*0.3f);
                 tempRotY = tempRotY.Rotation_Y(-deltaX*0.3f);

                 finalRot = tempRotX*finalRot*tempRotY;
             }
             oldX = mouseXPos;
             oldY = mouseYPos;
         });


        if (this->window->Open())
        {
//            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);
            //set clear color to gray
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            return true;
        }
        return false;
    }

    //------------------------------------------------------------------------------


    void
    ExampleApp::Run()
    {
        skeleton = new Skeleton();
        glUseProgram(skeleton->shader->program);

        skeleton->shader->Apply();
        skeleton->ReadFromFile("Unit_Footman.constants");
        skeleton->CalculateOriginal();

        anim = new Animation();
        anim->SetupNax3("Unit_Footman.nax3");

        skin = new Skinning();
        skin->ReadHeadData("Unit_Footman.nvx2");
        skin->SetupVertex();
        skin->SetupVertexBuffer();
        skin->SetupIndiceBuffer();
        skin->LoadDDS("Footman_Diffuse.dds", skeleton, 0);
        skin->LoadDDS("Footman_Specular.dds", skeleton, 1);
        skin->LoadDDS("Footman_Normal.dds", skeleton, 2);
        float dt = 0.0001f;
        while (this->window->IsOpen())
        {
            std::chrono::time_point<std::chrono::system_clock> start, end;

            start = std::chrono::system_clock::now();
            if (moveUP)
            {
                flash += 0.01f;
            }
            else if (moveDown)
            {
                flash -= 0.01f;
            }
            else if (moveLeft)
            {
                speedyGonzales -= 0.01f;
            }
            else if (moveRight)
            {
                speedyGonzales += 0.01f;
            }

            finalRot.Set_Position(speedyGonzales, flash, 0);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            this->window->Update();
            skeleton->test = finalRot;

            anim->SetupAnimation(animation, skeleton, dt);
            skin->DrawSkin(skeleton);

            skeleton->DrawAnimations();
            this->window->SwapBuffers();
            end = std::chrono::system_clock::now();

            std::chrono::duration<float> elapsed_seconds = end-start;

            dt=elapsed_seconds.count() * 1000;
        }
    }

} // namespace Example