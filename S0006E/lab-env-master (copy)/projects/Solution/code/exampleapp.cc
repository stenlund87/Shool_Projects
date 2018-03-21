//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "GraphicsNode.h"
#include <iostream>
#include "SoftwareRendering.h"


TextureResource tex;
MeshResource* mesh;
ShaderObject bla;
LightNode lightyGonzales;

GraphicsNode graphics;

Matrix4D camera;
Matrix4D movement;
Matrix4D tempRotX;
Matrix4D tempRotY;
Matrix4D rotation;
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
					//std::cout << finalRot[0][0] << ":" << finalRot[0][1] << ":" << finalRot[0][2] << ":" << finalRot[0][3] << ":" << std::endl;
					//std::cout << finalRot[1][0] << ":" << finalRot[1][1] << ":" << finalRot[1][2] << ":" << finalRot[2][3] << ":" << std::endl;
					//std::cout << finalRot[2][0] << ":" << finalRot[2][1] << ":" << finalRot[2][2] << ":" << finalRot[2][3] << ":" << std::endl;
					//std::cout << finalRot[3][0] << ":" << finalRot[3][1] << ":" << finalRot[3][2] << ":" << finalRot[3][3] << ":" << std::endl;
					//std::cout << "" << std::endl;
					//std::cout << "" << std::endl;
				}
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
			//finalRot = finalRot.Rotation_Y(180.0f);

			glEnable(GL_CULL_FACE);
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
		Vector4D eye(0, 0, 2);
		Vector4D target(0,0,0);
		Vector4D up(0, 1, 0);

		Matrix4D rastRot;
		Matrix4D projection;
		Matrix4D view;
		Matrix4D MVP;

		projection = projection.Projection();
		view = view.LookAt(eye, target, up);
		graphics.InitRasterizer();

		Matrix4D viewProj = projection*view;

		lightyGonzales.SetPos(0.0f, 0.0f, 0.2f);
		lightyGonzales.SetAmb(0.2f, 0.2f, 0.2f);
		lightyGonzales.SetDiff(0.1f, 0.1f, 0.1f);
		lightyGonzales.SetSpec(1.0f, 1.0f, 1.0f);
		lightyGonzales.SetIntensity(70.0f);
		graphics.shaderObj->light = lightyGonzales;

		SoftwareRendering sr(viewProj, graphics.GetTexturePointer());
		sr.SetLight(lightyGonzales);

		bool edgeOfWindow = true;

		while (this->window->IsOpen())
		{
			glClear(GL_COLOR_BUFFER_BIT);
			this->window->Update();

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
			MVP = projection * view * finalRot;
			rastRot.Set_Position(speedyGonzales, flash, 0);
			sr.SetModelMatrix(finalRot);
			sr.Draw();
			graphics.Draw();
			this->window->SwapBuffers();
		}
	}

} // namespace Example
