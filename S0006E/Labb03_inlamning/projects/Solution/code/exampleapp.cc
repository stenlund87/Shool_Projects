//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "MeshResource.h"
#include "TextureResource.h"
#include <iostream>




const GLchar* vs =
"#version 430\n"
"uniform mat4 matrix;\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec2 UV;\n"
"layout(location=0) out vec2 uv;\n"
//"layout(location=1) in vec4 color;\n"
//"layout(location=0) out vec4 Color;\n"
"void main()\n"
"{\n"
"	gl_Position = matrix * vec4(pos, 1);\n"
"   uv.x = UV.x;\n"
"   uv.y = 1- UV.y;\n"
//"	Color = color;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
//"layout(location=0) in vec4 color;\n"
"layout(location=0) in vec2 UV;\n"
"out vec3 Color;\n"
"uniform sampler2D texSampler;\n"  //Ny rad
//"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = texture(texSampler,UV).rgb;\n"
"}\n";
TextureResource tex;
MeshResource* mesh;

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
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close(); 
	});
	
	//GLfloat buf[] =
	//{
	//	-0.5f,	-0.5f,	-1,			// pos 0
	//	1,		0,		0,		1,	// color 0
	//	0.5f,		0.5f,	-1,			// pos 1
	//	0,		1,		0,		1,	// color 0
	//	0.5f,	-0.5f,	-1,			// pos 2
	//	0,		0,		1,		1	// color 0
	//};

	//GLfloat buf2[] =
	//{
	//	-0.5f,	-0.5f,	-1,			// pos 0
	//	1,		0,		0,		1,	// color 0
	//	-0.5f,		0.5f,	-1,			// pos 1
	//	0,		1,		0,		1,	// color 0
	//	0.5f,	0.5f,	-1,			// pos 2
	//	0,		0,		1,		1	// color 0
	//};

	if (this->window->Open())
	{
		glEnable(GL_CULL_FACE);
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
		//e.MakeQuad();
	
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
	MeshResource mesh = MeshResource::MakeCube();
	Matrix4D finalRot;

	Matrix4D tempRotX;
	Matrix4D tempRotY;
	Matrix4D tempRotZ;

	Matrix4D rotation;

	Matrix4D movement;
	//tex.SetupTexture();
	tex.LoadFromFile("D:\\Zelda3.jpg");
	tex.SetupTexture();
	//tex.ActivateTexture();

	int speedyGonzales = 0;
	int rotDegree = 0;
	bool edgeOfWindow = true;


	float root = std::sqrt(0.5f);

	while (this->window->IsOpen())
	{
		rotDegree++;
		if (edgeOfWindow)
		{
			speedyGonzales++;
		}
		else
		{
			speedyGonzales--;
		}
		if (speedyGonzales < -70 || speedyGonzales>70)
		{
			edgeOfWindow = !edgeOfWindow;
		}

		if (rotDegree == 360)
		{
			rotDegree = 0;
		}
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		glUseProgram(this->program);

		// do stuff
		//glBindBuffer(GL_ARRAY_BUFFER, e.vbo);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.ebo);

		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);


		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 8, NULL);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 8, (GLvoid*)(sizeof(float32) * 4));


		//tempRotX = rotation.Rotation_X(rotDegree);
		tempRotY = rotation.Rotation_Y(rotDegree);
		tempRotZ = rotation.Rotation_Z(rotDegree);
		//finalRot = tempRotY ;
		finalRot = tempRotX*tempRotY*tempRotZ;
		movement.Set_Position(speedyGonzales*0.01f, 0, 0);

		finalRot = movement * finalRot;
		
		
		GLuint matrixLocation = glGetUniformLocation(program, "matrix");
		glUniformMatrix4fv(matrixLocation, 1, GL_TRUE, (GLfloat*)finalRot.matrix);

		mesh.Draw();
		/*	glUniformMatrix4fv(matLoc, 1, GL_TRUE, finalRot.glArr);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);*/

		this->window->SwapBuffers();
	}
}

} // namespace Example
