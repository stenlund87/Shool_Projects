#include "Shape.h"
#pragma once

Triangle::Triangle(float b, float h)
{
	base = b;
	height = h;
}


void Triangle::Set_Pos(float x, float y)
{
	homogen_matrix.matrix[0][2] = x;
	homogen_matrix.matrix[1][2] = y;
}

float Triangle::Get(int index)
{
	if (index <= 1 && index >= 0)
		return this->homogen_matrix.matrix[index][2];
	else
		return this->homogen_matrix.matrix[1][2];
}

void Triangle::Render()
{
	Example::AssignmentApp::LineData dots;
	float half_base = base/2;
	float half_height = height/2;

	Vector2D bottom_left(-half_base,-half_height);
	Vector2D bottom_right(half_base,-half_height);
	Vector2D top(-half_base, half_height);

	dots.c1 = shape_colour;
	dots.c2 = shape_colour;

	//Bottom of Triangle
	dots.x1 = homogen_matrix.Tranformation(bottom_left).Get(0);
	dots.y1 = homogen_matrix.Tranformation(bottom_left).Get(1);
	dots.x2 = homogen_matrix.Tranformation(bottom_right).Get(0);
	dots.y2 = homogen_matrix.Tranformation(bottom_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	////Left side of Triangle
	dots.x1 = homogen_matrix.Tranformation(bottom_left).Get(0);
	dots.y1 = homogen_matrix.Tranformation(bottom_left).Get(1);
	dots.x2 = homogen_matrix.Tranformation(top).Get(0);
	dots.y2 = homogen_matrix.Tranformation(top).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Right side of Triangle
	dots.x1 = homogen_matrix.Tranformation(bottom_right).Get(0);
	dots.y1 = homogen_matrix.Tranformation(bottom_right).Get(1);
	dots.x2 = homogen_matrix.Tranformation(top).Get(0);
	dots.y2 = homogen_matrix.Tranformation(top).Get(1);
	Example::AssignmentApp::DrawLine(dots);
}

float Triangle::Get_Size()
{
	return base/2;
}