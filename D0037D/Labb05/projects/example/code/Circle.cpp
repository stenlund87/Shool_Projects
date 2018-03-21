#include "Shape.h"
#include <math.h>
#include "Vector_Matrix.h"
#pragma once


Circle::Circle(float rad)
{
	radius = rad;
}

Circle::Circle()
{
}

void Circle::Set_Pos(float x, float y)
{
	homogen_matrix.matrix[0][2] = x;
	homogen_matrix.matrix[1][2] = y;
}

float Circle::Get(int index)
{
	if (index <= 1 && index >= 0)
		return this->homogen_matrix.matrix[index][2];
	else
		return this->homogen_matrix.matrix[1][2];
}

void Circle::Render()
{
	double rad = 3.14592/180;
	Example::AssignmentApp::LineData dots;
	dots.c1 = shape_colour;
	dots.c2 = shape_colour;

	const int numsteps = 10000;
	const float stepsize = 365 / float(numsteps);
	for (int i=1; i<=numsteps; i++)
	{
		float x1 = radius*cos(((i-1) * stepsize)*rad);
		float y1 = radius*sin(((i-1) * stepsize)*rad);
		float x2 = radius*cos(i * stepsize*rad);
		float y2 = radius*sin(i * stepsize*rad);
		Vector2D p1(x1,y1);
		Vector2D p2(x2, y2);
		Vector2D point_1 = homogen_matrix.Tranformation(p1);
		Vector2D point_2 = homogen_matrix.Tranformation(p2);

		dots.x1 = point_1.Get(0);
		dots.y1 = point_1.Get(1);
		dots.x2 = point_2.Get(0);
		dots.y2 = point_2.Get(1);
		Example::AssignmentApp::DrawLine(dots);
	}
}

bool Circle::Collision(Shape& other)
{
		if (&other == static_cast<Shape *>(this) )
			return false;
		Vector2D ball = this->Get_Position();
		Vector2D object_pos = other.Get_Position();
		Vector2D diff = object_pos - ball;

		double diff_x = std::abs(object_pos.Get(0) - ball.Get(0));
		double diff_y = std::abs(object_pos.Get(1) - ball.Get(1));
		double size = this->Get_Size() + other.Get_Size();

		if (diff_x <= size && diff_y <= size)
		{
			return true;
		}
		return false;
}

float Circle::Get_Size()
{
	return radius;
}
