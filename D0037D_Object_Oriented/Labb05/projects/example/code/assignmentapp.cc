//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "assignmentapp.h"
#include "Shape.h"
#include <render/window.h>
#include <time.h>
#include <cstdlib>



namespace Example
{
//------------------------------------------------------------------------------
/**
*/
AssignmentApp::AssignmentApp() 
{	
	ball = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
AssignmentApp::~AssignmentApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
void 
AssignmentApp::Setup()
{
	srand (time(0));
	ball = new Circle(0.05);
	ball->Set_Pos(0,0);
	ball->Set_Colour(1,1,1);
	ball->Set_Rotation(45);
	ball->Set_Velocity(0.01,0.025);
	saved_shapes.push_back(ball);	

	Square* new_square = new Square(0.07);
	new_square->Set_Pos(0,0);
	new_square->Set_Colour(0,1,0);
	new_square->Set_Rotation(45);
	new_square->Set_Velocity(0,0);
	saved_shapes.push_back(new_square);

	Display::Window * window = this->GetWindow();
	window->SetKeyPressFunction(
		[this](int key,int,int action,int mod)
		{
			this->KeyEvent(key, action, mod);
		}
	);
}

//------------------------------------------------------------------------------
/**
*/
void
AssignmentApp::Update()
{
	for (unsigned int i=0; i<saved_shapes.size();i++)
	{
		saved_shapes[i]->Update();
		saved_shapes[i]->Render();
	}

	for (unsigned int i = saved_shapes.size(); i>0;i--)
	{
		if(ball->Collision(*saved_shapes[i-1]))
		{
			Vector2D refl = ball->Shape_Reflection(*saved_shapes[i-1]);
			Delete_at_indx(i-1);
			ball->Set_Velocity(refl.Get(0),refl.Get(1));
		}
	}
}

int AssignmentApp::KeyEvent(int key, int action, int modifier)
{
	int rot = (rand() %3600)/10;
	float len = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float x1 = (rand()%100)/100.0f;
	float x2 = (rand()%100)/100.0f;
	float y1 = (rand()%100)/100.0f;
	float y2 = (rand()%100)/100.0f;
	float red = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float blue = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float green = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float base = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float height = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float x_vel = (rand()%1000)/100000.0f;
	float y_vel = (rand()%1000)/100000.0f;
	float x = x1-x2;
	float y = y1-y2;

	switch (key) 
	{
		case 0x31: //1
		{
			Square* new_square = new Square(0.1);
			new_square->Set_Pos(x,y);
			new_square->Set_Colour(red,blue,green);
			new_square->Set_Rotation(rot);
			//new_square->Set_Velocity(x_vel,y_vel);
			saved_shapes.push_back(new_square);
			break;
		}

		case 0x32: //2
		{
			Triangle* new_triangle = new Triangle(0.2, 0.1);
			new_triangle->Set_Pos(x,y);
			new_triangle->Set_Colour(red,blue,green);
			new_triangle->Set_Rotation(rot);
			//new_triangle->Set_Velocity(x_vel,y_vel);
			saved_shapes.push_back(new_triangle);
			break;
		}

		case 0x33: //3
		{
			Circle* new_circle = new Circle(0.05);	
			new_circle->Set_Pos(x,y);
			new_circle->Set_Colour(red,blue,green);
			new_circle->Set_Rotation(rot);
			//new_circle->Set_Velocity(x_vel,y_vel);
			saved_shapes.push_back(new_circle);
			break;
		}
		
		case 0x51: //Q
		{
			Delete_Object(typeid(Square));
			break;
		}

		case 0x57: //W
		{
			Delete_Object(typeid(Triangle));
			break;
		}
		case 0x45: //E
		{
			Delete_Object(typeid(Circle));
			break;
		}
	}
	return 0;
}


void AssignmentApp::Delete_Object(const std::type_info& object_type)
{
	Shape* temp;

	for (unsigned int i = saved_shapes.size(); i>1; i--)
	{
		if (typeid(*saved_shapes[i-1]) == object_type)
		{
			temp = saved_shapes[i-1];
			saved_shapes.erase(saved_shapes.begin() + i-1);
			delete temp;
		}
	}
}

void AssignmentApp::Delete_at_indx(const int indx)
{
	Shape* temp;
	temp = saved_shapes[indx];
	saved_shapes.erase(saved_shapes.begin()+indx);
	delete temp;
}




} // namespace Example