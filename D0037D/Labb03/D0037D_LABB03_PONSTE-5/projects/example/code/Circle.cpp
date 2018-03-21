#include "Shape.h"
#include <math.h>
#include "Vector_Matrix.h"
#pragma once


Circle::Circle(float rad)
{
	radius = rad;
}


void Circle::Set_Pos(float x, float y)
{
	pos.coordinates[0] = x;
	pos.coordinates[1] = y;
}


void Circle::Render()
{
	
	float rad = 3.14592/180;
	Example::AssignmentApp::LineData dots;
	dots.c1 = shape_colour;
	dots.c2 = shape_colour;


	for (int i=1; i<360; i++)
	{
		float x1 = radius*cos((i-1)*rad);
		float y1 = radius*sin((i-1)*rad);
		float x2 = radius*cos(i*rad);
		float y2 = radius*sin(i*rad);
		Vector2D p1(x1,y1);
		Vector2D p2(x2, y2);

		dots.x1 = pos.coordinates[0] + rotation.Tranformation(p1).Get(0);
		dots.y1 = pos.coordinates[1] + rotation.Tranformation(p1).Get(1);
		dots.x2 = pos.coordinates[0] + rotation.Tranformation(p2).Get(0);
		dots.y2 = pos.coordinates[1] + rotation.Tranformation(p2).Get(1);
		Example::AssignmentApp::DrawLine(dots);



	}

}
