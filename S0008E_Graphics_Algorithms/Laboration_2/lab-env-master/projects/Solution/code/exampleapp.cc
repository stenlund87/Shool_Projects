//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#ifndef EXAMPLEAPP_CC
#define EXAMPLEAPP_CC


#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <GL/glut.h>
#include "Skeleton.h"
#include "Animation.h"
#include <chrono>


const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(pos *0.2 , 1);\n"
"	Color = color;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"}\n";

Skeleton *skeleton;
int currentAnimation = 0;

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
            if (key == GLFW_KEY_1)
            {
                currentAnimation = 0;
            }
            else if (key == GLFW_KEY_2)
            {
                currentAnimation = 1;
            }
            else if (key == GLFW_KEY_3)
            {
                currentAnimation = 2;
            }
            else if (key == GLFW_KEY_4)
            {
                currentAnimation = 3;
            }
            else if (key == GLFW_KEY_5)
            {
                currentAnimation = 4;
            }
            else if (key == GLFW_KEY_6)
            {
                currentAnimation = 5;
            }
            else if (key == GLFW_KEY_7)
            {
                currentAnimation = 6;
            }
            else if (key == GLFW_KEY_8)
            {
                currentAnimation = 7;
            }
            else if (key == GLFW_KEY_ESCAPE)
            {
                this->window->Close();
            }
        }
        else if (action == GLFW_RELEASE)
        {

        }
	});

	GLfloat buf[] =
	{
		-0.5f,	-0.5f,	-1,			// pos 0
		1,		0,		0,		1,	// color 0
		0,		0.5f,	-1,			// pos 1
		0,		1,		0,		1,	// color 0
		0.5f,	-0.5f,	-1,			// pos 2
		0,		0,		1,		1	// color 0
	};

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

		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	skeleton = new Skeleton();
	skeleton->ReadFromFile("Unit_Footman.constants");
    Animation* anim = new Animation();
    anim->SetupNax3("Unit_Footman.nax3");
	//MeshResource e;
    float dt = 0.0001f;
	while (this->window->IsOpen())
	{
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();

        glClear(GL_COLOR_BUFFER_BIT);

		this->window->Update();

        anim->SetupAnimation(currentAnimation,skeleton,dt);

		this->window->SwapBuffers();

        end = std::chrono::system_clock::now();

        std::chrono::duration<float> elapsed_seconds = end-start;

        dt=elapsed_seconds.count() * 1000;
	}
}

} // namespace Example
#endif // !EXAMPLEAPP_CC