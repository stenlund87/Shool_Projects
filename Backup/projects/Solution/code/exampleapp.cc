//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include "MeshResource.h"
#include "TextureResource.h"
#include "Octree.h"
#include <cstring>
#include <chrono>

const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec2 UV;\n"
"layout(location=2) in vec3 normal;\n"
"layout(location=0) out vec2 uv;\n"
"uniform mat4 MVP;\n"
"void main()\n"
"{\n"
"   "
"	gl_Position = MVP * vec4(pos, 1);\n"
"   uv.x = UV.x;\n"
"   uv.y = 1- UV.y;\n"

"}\n";

const GLchar* ps =
"#version 430\n"
"layout(location=0) in vec2 UV;\n"
"out vec3 Color;\n"
"uniform sampler2D texSampler;\n"
"void main()\n"
"{\n"
"	Color = texture(texSampler,UV).rgb;\n"
"}\n";


bool mousePressed = false;
bool intersected = false;
float mouseX = 0;
float mouseY = 0;

MeshResource* mesh;

Vector4D point;
Vector4D ray_clip;
Vector4D ray_eye;
Vector4D ray_wor;
Vector4D eye;
Vector4D target;
Vector4D up;

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
bool rPressed = false;
bool ePressed = false;

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
					case GLFW_KEY_R:
						rPressed = !rPressed;
						break;
                    case GLFW_KEY_E:
						ePressed = !ePressed;
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
    TextureResource* black = new TextureResource();


	identiy = Matrix4D();

	eye = Vector4D(0,0,1);
	target = Vector4D(0,0,0);
	up = Vector4D(0,1,0);

	aspect = float(this->window->GetWidth())/float(this->window->GetHeight());
	top = near*tan((M_PI/180.0f)*(fov*0.5));
	bottom = - top;
	right = top*aspect;
	left = -right;

	location = glGetUniformLocation(this->program, "MVP");
	view = view.LookAt(eye,target,up);
    projection = projection.Projection();

	mesh = new MeshResource();
	mesh->Load("cube.obj");
//    Octree* t = new Octree(*mesh);


    mesh->SetPosition(Vector4D(0,0,-2.0f));
    mesh->CalculateModelMatrix();
//	mesh->CalculateAABB();

    tr->LoadFromFile("zelda.jpg");
    black->LoadFromFile("Black.jpg");
//    tree->Cleanup();
	Octree* tree = new Octree(mesh->box,mesh->verticeBuffer, mesh->edges, mesh->faces ,mesh->num, mesh);
	float xMove = 0;
	float zMove = 1.0f;

	float dt = 0.00016f;

	Matrix4D viewProj = projection*view;

    while (this->window->IsOpen())
	{

        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
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


        mesh->rotation = rotation;
        mesh->wireframe = rPressed;
        mesh->CalculateModelMatrix();
//        mesh->CalculateAABB();



        MVP = projection*view*mesh->model;
        glUniformMatrix4fv(location,1,GL_TRUE, (float*)MVP.matrix);
        if(rPressed)
        {
            black->Apply();
            tree->DrawTree();
//			tree->DrawPoints();
        }
        else
        {
            tr->Apply();
			mesh->wireframe = ePressed;
            mesh->Draw();
//			tree->DrawTree();


			MVP = projection * view * identiy;
            glUniformMatrix4fv(location,1,GL_TRUE, (float*)MVP.matrix);
//            mesh->DrawBorders();
        }

		this->window->SwapBuffers();

		end = std::chrono::system_clock::now();

		std::chrono::duration<float> elapsed_seconds = end-start;

		dt=elapsed_seconds.count();

    }
}

} // namespace Example