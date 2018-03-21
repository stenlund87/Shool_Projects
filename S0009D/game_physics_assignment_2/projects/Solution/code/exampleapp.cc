//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include "MeshResource.h"
#include "Ray.h"
#include "TextureResource.h"
#include <cstring>

const GLchar* vs =
        "#version 430\n"
                "layout(location=0) in vec3 pos;\n"
                "layout(location=1) in vec2 UV;\n"
                "layout(location=2) in vec3 normal;\n"
                "layout(location=3) in vec4 vertexColor;\n"
                "layout(location=0) out vec2 uv;\n"
                "layout(location=1) out vec4 color;\n"
                "uniform mat4 MVP;\n"
                "uniform vec4 testColor;\n"
                "void main()\n"
                "{\n"
                "   "
                "	gl_Position = MVP * vec4(pos, 1);\n"
                "   uv.x = UV.x;\n"
                "   uv.y = 1- UV.y;\n"
                "   color = testColor;\n"

                "}\n";

const GLchar* ps =
        "#version 430\n"
                "layout(location=0) in vec2 UV;\n"
                "layout(location=1) in vec4 color;\n"
                "out vec3 Color;\n"
                "uniform sampler2D texSampler;\n"
                "void main()\n"
                "{\n"
                "	Color = texture(texSampler,UV).rgb + color.xyz;\n"
                "}\n";



Ray ray;
bool mousePressed = false;
bool intersected = false;
float mouseX = 0;
float mouseY = 0;
std::vector<MeshResource> quads;
Vector4D point;
Vector4D ray_clip;
Vector4D ray_eye;
Vector4D ray_wor;
Vector4D eye;
Vector4D target;
Vector4D up;

Vector4D globalKingMasterEliteIntersect1337;

Matrix4D rotation;
Matrix4D view;
Matrix4D projection;
Matrix4D MVP;
Matrix4D tempRotX;
Matrix4D tempRotY;
Matrix4D identiy;
Matrix4D rot;


float near = 1.0f;
float far = 10.0f;
float fov = 90.0f;
float aspect = 0;
float top = 0;
float bottom = 0;
float right = 0;
float left = 0;

bool selected = false;

bool aPressed = false;
bool dPressed = false;
bool wPressed = false;
bool sPressed = false;

float f = 0;
float oldX = 0;
float oldY = 0;
GLint location = 10;
GLint colorLocation = 0;

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
                                        switch(action)
                                        {
                                            case GLFW_PRESS:
                                                switch (key)
                                                {
                                                    case GLFW_KEY_ESCAPE:
                                                        this->window->Close();
                                                        break;
                                                    case GLFW_KEY_W:
                                                        wPressed = true;
                                                        break;
                                                    case GLFW_KEY_A:
                                                        aPressed = true;
                                                        break;
                                                    case GLFW_KEY_S:
                                                        sPressed = true;
                                                        break;
                                                    case GLFW_KEY_D:
                                                        dPressed = true;
                                                        break;
                                                }
                                                break;
                                            case GLFW_RELEASE:
                                                switch (key)
                                                {
                                                    case GLFW_KEY_W:
                                                        wPressed = false;
                                                        break;
                                                    case GLFW_KEY_A:
                                                        aPressed = false;
                                                        break;
                                                    case GLFW_KEY_S:
                                                        sPressed = false;
                                                        break;
                                                    case GLFW_KEY_D:
                                                        dPressed = false;
                                                        break;
                                                }

                                                break;
                                        }
                                    });

        window->SetMousePressFunction([this](int32 left, int32 pressed, int32 modifier)
                                      {
                                          if (left == GLFW_MOUSE_BUTTON_LEFT && pressed == GLFW_PRESS)
                                          {
                                              bool intersect[quads.size()];
                                              ray_clip[0] = mouseX;
                                              ray_clip[1] = mouseY;
                                              ray_clip[2] = -1.0f;
                                              ray_clip[3] = 1.0f;
                                              ray_eye = projection.Inverse() * ray_clip;
                                              ray_eye[2] = -1.0f;
                                              ray_eye[3] = 0;

                                              ray_wor = (view.Inverse()*ray_eye).Normalize();
//                                              ray_wor.Normalize();
                                              ray = Ray(eye, ray_wor);
                                              intersected = false;
                                              for(int i = 0; i < quads.size(); i++)
                                              {
                                                  for(int p = 0; p < 6; p++)
                                                  {
                                                      quads[i].color = Vector4D(1,0,0);
                                                      point = ray.Intersect(quads[i].plane[p]);
                                                      if(point[3] > 0)
                                                      {
                                                          intersected = true;
                                                          intersect[i] = ray.BoundingBoxIntersect(quads[i].box, globalKingMasterEliteIntersect1337);
                                                          if(!intersect[i])
                                                          {
                                                              intersect[i] = ray.PointInside(quads[i].plane[p], point);
                                                          }
                                                      }
                                                  }

                                              }
                                              for(int j = 0; j < quads.size()-1; j++)
                                              {
                                                  if(intersect[j])
                                                  {
                                                      if(intersect[j+1])
                                                      {
                                                          for(int k = 0; k < 6; k++)
                                                          {
                                                              if(quads[j].plane[k].center[2] > quads[j+1].plane[k].center[2])
                                                              {
                                                                  quads[j+1].color = Vector4D(0,1,0);
                                                                  quads[j+1].selected = true;
                                                                  quads[j+1].physics.force = ray_wor;
                                                                  quads[j+1].physics.force[2] = 0;
                                                                  quads[j+1].physics.force[3] = 1.0f;
                                                              }
                                                          }

                                                      }
                                                      else
                                                      {
                                                          quads[j].color = Vector4D(0,1,0);
                                                          quads[j].intersectPoint = point;

                                                      }
                                                  }
                                                  else if(intersect[j+1])
                                                  {
                                                      quads[j+1].color = Vector4D(0,1,0);
                                                      quads[j+1].selected = true;
                                                      quads[j+1].physics.force = ray_wor*5;
                                                      quads[j+1].intersectPoint = globalKingMasterEliteIntersect1337;
                                                  }
                                              }

                                          }
                                          else if (left == GLFW_MOUSE_BUTTON_RIGHT && pressed == GLFW_PRESS)
                                          {
                                              mousePressed = true;
                                          }
                                          else if (left == GLFW_MOUSE_BUTTON_RIGHT && pressed == GLFW_RELEASE)
                                          {
                                              mousePressed = false;
                                          }
                                      }
        );


        window->SetMouseMoveFunction([this](float64 mouseXPos, float64 mouseYPos)
                                     {
                                         mouseX = (2.0f*(float)mouseXPos)/this->window->GetWidth() - 1.0f;
                                         mouseY = 1.0f-(2.0f*(float)mouseYPos)/this->window->GetHeight();

                                         float deltaX = (float)mouseXPos - oldX;
                                         float deltaY = (float)mouseYPos - oldY;
                                         if (mousePressed)
                                         {
                                             tempRotX = tempRotX.Rotation_X(-deltaY*0.3f);
                                             tempRotY = tempRotY.Rotation_Y(-deltaX*0.3f);
                                             eye = tempRotY * eye;
                                             view = view.LookAt(eye,target,up);
                                             rotation = tempRotX*rotation*tempRotY;
                                         }

                                         oldX = (float)mouseXPos;
                                         oldY = (float)mouseYPos;

                                     });


        if (this->window->Open())
        {
            // set clear color to gray
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            // setup vertex shader
            this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
            GLint length = std::strlen(vs);
            glShaderSource(this->vertexShader, 1, &vs, &length);
            glCompileShader(this->vertexShader);

            // get error log
            GLint shaderLogSize;
            glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
            if (shaderLogSize > 0)
            {
                GLchar* buf = new GLchar[shaderLogSize];
                glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
                printf("[SHADER COMPILE ERROR]: %s", buf);
                delete[] buf;
            }

            // setup pixel shader
            this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
            length = std::strlen(ps);
            glShaderSource(this->pixelShader, 1, &ps, &length);
            glCompileShader(this->pixelShader);

            // get error log
            shaderLogSize;
            glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
            if (shaderLogSize > 0)
            {
                GLchar* buf = new GLchar[shaderLogSize];
                glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
                printf("[SHADER COMPILE ERROR]: %s", buf);
                delete[] buf;
            }

            // create a program object
            this->program = glCreateProgram();
            glAttachShader(this->program, this->vertexShader);
            glAttachShader(this->program, this->pixelShader);
            glLinkProgram(this->program);
            glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
            if (shaderLogSize > 0)
            {

                GLchar* buf = new GLchar[shaderLogSize];
                glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
                printf("[PROGRAM LINK ERROR]: %s", buf);
                delete[] buf;
            }
            glEnable(GL_DEPTH_TEST);
            return true;
        }
        return false;
    }

//------------------------------------------------------------------------------
/**
*/
    void
    ExampleApp::Run()
    {
        TextureResource* tr = new TextureResource();
        globalKingMasterEliteIntersect1337 = Vector4D(0,0,0);
        identiy = Matrix4D();
        quads = std::vector<MeshResource>(2);

        eye = Vector4D(0,0,1);
        target = Vector4D(0,0,0);
        up = Vector4D(0,1,0);

        aspect = float(this->window->GetWidth())/float(this->window->GetHeight());
        top = near*tan((M_PI/180.0f)*(fov*0.5));
        bottom = - top;
        right = top*aspect;
        left = -right;

        location = glGetUniformLocation(this->program, "MVP");
        colorLocation = glGetUniformLocation(this->program, "testColor");
        view = view.LookAt(eye,target,up);

        projection = projection.Projection();
        Vector4D extends(0.5f,.50f,0.5f);

        quads[0].MakeQuad(0.1f,Vector4D(0,-2,-1.0f));
        quads[1].Load("cube.obj");
        quads[1].SetPosition(Vector4D(0,0,-2));
        quads[1].physics.shapeMatrix = projection.InertiaTensorCube(extends,10.0f);
        quads[1].physics.mass = 10.0f;
        quads[1].InverseInertiaTensor();
        quads[1].CalculateModelMatrix();

        tr->LoadFromFile("zelda.jpg");

        Vector4D bla(0.5,-4,3);
        bla.Normalize();

        float angle = 0;
        float xMove = 0;
        float zMove = 1.0f;

        Vector4D pos;
        float dt = 0.00016f;



        while (this->window->IsOpen())
        {
            glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
            this->window->Update();
            glUseProgram(this->program);


            if(aPressed) {xMove -= 0.01f;}

            if(dPressed) {xMove+= 0.01f;}

            if(wPressed) {zMove -= 0.01f; }

            if(sPressed){ zMove += 0.01f;}

            eye = Vector4D(xMove,0,zMove);
            target = Vector4D(xMove,0,-zMove);


            view = view.LookAt(eye,target,up);


            angle += 0.01f;

            for(int i = 0; i < quads.size(); i++)
            {
                quads[i].Update(globalKingMasterEliteIntersect1337, dt);
                quads[i].CalculateModelMatrix();
                quads[i].CalculateAABB(quads[i].model);
                MVP = projection*view*quads[i].model;
                glUniformMatrix4fv(location,1,GL_TRUE, (float*)MVP.matrix);
                glUniform4f(colorLocation, quads[i].color[0], quads[i].color[1], quads[i].color[2],1);
                tr->Apply();

                quads[i].Draw();

                MVP = projection * view * identiy;
                glUniformMatrix4fv(location,1,GL_TRUE, (float*)MVP.matrix);
                quads[i].DrawBorders();



            }
            if(intersected)
            {
                MVP = projection * view * identiy;
                glUniformMatrix4fv(location,1,GL_TRUE, (float*)MVP.matrix);
                glUniform4f(colorLocation, 1, 1, 1,1);
                glPointSize(10.0f);
                glBegin(GL_POINTS);
                glColor3i(1,1,1);
                glVertex3f(globalKingMasterEliteIntersect1337[0],globalKingMasterEliteIntersect1337[1],globalKingMasterEliteIntersect1337[2]);
                glEnd();
            }

            this->window->SwapBuffers();
        }
    }

} // namespace Example