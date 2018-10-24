//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "assignmentapp.h"
#include "Shape.h"



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
	// create your own objects 
	//Square* x = new Square(0.5);
	//saved_shapes.push_back(x);
	Triangle* y = new Triangle(0.3,0.3);
	saved_shapes.push_back(y);
	//Circle* z = new Circle(0.1f);
	//saved_shapes.push_back(z);
	f = 0.0f;
}

//------------------------------------------------------------------------------
/**
*/
void
AssignmentApp::Update()
{

	saved_shapes[0]->Set_Pos(0.2f,0.2f);
	saved_shapes[0]->Set_Colour(0.0f,0.0f,1.0f);
	saved_shapes[0]->Set_Rotation(10);
	saved_shapes[0]->Render();
	//saved_shapes[1]->Set_Pos(0.4f,0.4f);
	//saved_shapes[1]->Set_Colour(0.0f,1.0f,0.0f);
	//saved_shapes[1]->Set_Rotation(90);
	//saved_shapes[1]->Render();
	//saved_shapes[2]->Set_Pos(0.8f,0.8f);
	//saved_shapes[2]->Set_Colour(1.0f,0.0f,0.0f);
	//saved_shapes[2]->Render();

	//f += 0.1f;
	


	//demo line drawing code
	//LineData line;
	//line.x1 = -0.3f;
	//line.y1 = -0.3f;
	//line.x2 = 0.0f;
	//line.y2 = 0.5f;
	//line.c1.r = 1.0f;
	//AssignmentApp::DrawLine(line);	
	//line.x1 = 0.0f;
	//line.y1 = 0.5f;
	//line.x2 = 0.3f;
	//line.y2 = -0.3f;	
	//AssignmentApp::DrawLine(line);	
	//line.x1 = 0.3f;
	//line.y1 = -0.3f;
	//line.x2 = -0.3f;
	//line.y2 = -0.3f;
	//AssignmentApp::DrawLine(line);	
}

} // namespace Example