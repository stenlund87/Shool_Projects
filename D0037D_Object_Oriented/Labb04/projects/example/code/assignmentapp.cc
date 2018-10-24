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
	// empty
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
	Display::Window * window = this->GetWindow();
	window->SetKeyPressFunction(
		[this](int key,int,int action,int mod)
		{
			this->KeyEvent(key, action, mod);
		}
	);

	// create your own objects 
	//Square* x = new Square(0.5);
	//saved_shapes.push_back(x);
	//Triangle* y = new Triangle(0.3f,0.3f);
	//saved_shapes.push_back(y);
	//Triangle* j = new Triangle(0.3,0.3);
	//saved_shapes.push_back(j);
	//Circle* z = new Circle(0.1f);
	//saved_shapes.push_back(z);
	//f = 0.0f;
}

//------------------------------------------------------------------------------
/**
*/
void
AssignmentApp::Update()
{
	for (unsigned int i=0; i<saved_shapes.size();i++)
	{
	saved_shapes[i]->Render();
	}

}

int AssignmentApp::KeyEvent(int key, int action, int modifier)
{
	

	srand (time(NULL));
	int rot = rand() %360 + 0;
	float len = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float x = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float y = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float red = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float blue = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float green = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float base = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	float height = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
	srand(1);

	switch (key) 
	{
		case 0x31: //1
		{
			Square* new_square = new Square(len);
			new_square->Set_Pos(x,y);
			new_square->Set_Colour(red,blue,green);
			new_square->Set_Rotation(rot);
			saved_shapes.push_back(new_square);
			break;
		}

		case 0x32: //2
		{
			Triangle* new_triangle = new Triangle(base, height);
			new_triangle->Set_Pos(x,y);
			new_triangle->Set_Colour(red,blue,green);
			new_triangle->Set_Rotation(rot);
			saved_shapes.push_back(new_triangle);
			break;
		}

		case 0x33: //3
		{
			Circle* new_circle = new Circle(base);	
			new_circle->Set_Pos(x,y);
			new_circle->Set_Colour(red,blue,green);
			new_circle->Set_Rotation(rot);
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

	for (unsigned int i = saved_shapes.size(); i>0; i--)
	{
		if (typeid(*saved_shapes[i-1]) == object_type)
		{
			temp = saved_shapes[i-1];
			saved_shapes.erase(saved_shapes.begin() + i-1);
			delete temp;
		}
	}
}

} // namespace Example