//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "exampleapp.h"
#include "GraphicsNode.h"
#include "SoftwareRendering.h"
#include "HE_Mesh.h"




TextureResource tex;
MeshResource* mesh;
ShaderObject bla;
LightNode lightyGonzales;
SoftwareRendering swr;

HE_Mesh* hem;
GraphicsNode test;

Matrix4D camera;
Matrix4D movement;
Matrix4D tempRotX;
Matrix4D tempRotY;

Matrix4D finalRot;


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
				else if (key == GLFW_KEY_ESCAPE)
				{
					this->window->Close();
				}
				else if(key == GLFW_KEY_Q)
				{
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
				tempRotX = tempRotX.Rotation_X(-deltaY*0.3);
				tempRotY = tempRotY.Rotation_Y(-deltaX*0.3);

				finalRot = tempRotX*finalRot*tempRotY;

// 				hem->Rotate(finalRot);
			}

			oldX = mouseXPos;
			oldY = mouseYPos;

		});


		if (this->window->Open())
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------------

	
	void
		ExampleApp::Run()
	{
		test.InitHEM();
		lightyGonzales.SetPos(1000.0f, 1000.0f, 100.0f);
		lightyGonzales.SetAmb(0.0f, 0.0f, 0.0f);
		lightyGonzales.SetDiff(0.1f, 0.1f, 0.1f);
		lightyGonzales.SetSpec(1.0f, 1.0f, 1.0f);
		lightyGonzales.SetIntensity(40.0f);
		test.shaderObj->light = lightyGonzales;
		test.SubDivide();
//		test.SubDivide();

		while (this->window->IsOpen())
		{
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


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

			glUseProgram(this->program);

			test.SetTransform(finalRot, finalRot);

			test.DrawHEM();


			this->window->SwapBuffers();
		}
	}

} // namespace Example
