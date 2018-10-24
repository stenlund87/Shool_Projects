//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "GraphicsNode.h"
//#include "MeshResource.h"
//#include "TextureResource.h"
//#include "ShaderObject.h"
#include <iostream>




TextureResource tex;
MeshResource* mesh;
ShaderObject bla;

GraphicsNode test;

Matrix4D movement;
Matrix4D tempRotX;
Matrix4D tempRotY;
Matrix4D tempRotZ;
Matrix4D rotation;
Matrix4D finalRot;

Vector4D pos;

float speedyGonzales = 0;
float flash = 0;
bool mousePressed = false;

int mouseX = 0;
int mouseY = 0;

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
		switch (key)
		{
		case GLFW_KEY_W:
		{
			flash += 0.01f;
			finalRot.Set_Position(finalRot[0][3], flash, 0);
			break;
		}
		case GLFW_KEY_A:
		{	
			speedyGonzales -= 0.01f;
			finalRot.Set_Position(speedyGonzales, finalRot[1][3], 0);
			break;
		}
		case GLFW_KEY_S:
		{
			flash -= 0.01f;
			finalRot.Set_Position(finalRot[0][3], flash , 0);
			break;
		}
		case GLFW_KEY_D:
		{
			speedyGonzales += 0.01f;
			finalRot.Set_Position(speedyGonzales, finalRot[1][3], 0);
			break;
		}
		case GLFW_KEY_ESCAPE:
		{
			this->window->Close();
			break;
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
		if (mousePressed)
		{
			tempRotX = tempRotX.Rotation_X((mouseYPos*0.003f));
			tempRotY = tempRotY.Rotation_Y((mouseXPos*0.003f));
			finalRot = finalRot * tempRotX*tempRotY;
		}
		//mouseX = mouseXPos - mouseX*0.001f;
		//mouseY = mouseYPos - mouseY*0.001f;
	});


	if (this->window->Open())
	{
		glEnable(GL_CULL_FACE);
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
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


	//MeshResource mesh = MeshResource::MakeCube();








	//tex.LoadFromFile("D:\\Zelda3.jpg");
	//tex.SetupTexture();

	int speedyGonzales = 0;
	int rotDegree = 0;
	bool edgeOfWindow = true;

	test.InitNode();

	while (this->window->IsOpen())
	{

		/* Fungerar */
		//bla.LoadShader("D:\\verticeShader.txt", "D:\\ps.txt");
		//rotDegree++;
		/*	if (edgeOfWindow)
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
			}*/
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();
		//bla.Apply();

		//tempRotX = rotation.Rotation_X(rotDegree);
		//tempRotY = rotation.Rotation_Y(rotDegree);
		//tempRotZ = rotation.Rotation_Z(rotDegree);


		//movement.Set_Position(speedyGonzales*0.01f, 0, 0);

		//finalRot = movement * finalRot;

		test.Draw(*finalRot.matrix);
		//bla.ModifyMatrix("matrix", *finalRot.matrix);
		//GLuint matrixLocation = glGetUniformLocation(bla.program, "matrix");
		//glUniformMatrix4fv(matrixLocation, 1, GL_TRUE, (GLfloat*)finalRot.matrix);

		//mesh.Draw();
		this->window->SwapBuffers();
	}
}

} // namespace Example
