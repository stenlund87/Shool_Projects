#include "Shape.h"

#pragma once

Square::Square(float lenght)
{
	lenght_side = lenght;
}

Square::~Square()
{
}

void Square::Set_Pos(float x, float y)
{
	homogen_matrix.matrix[0][2] = x;
	homogen_matrix.matrix[1][2] = y;
}

float Square::Get(int index)
{
	if (index <= 1 && index >= 0)
		return this->homogen_matrix.matrix[index][2];
	else
		return this->homogen_matrix.matrix[1][2];
}

void Square::Render()
{
	float half_lenght = lenght_side/2;
	Vector2D bottom_right(half_lenght,half_lenght);
	Vector2D bottom_left(-half_lenght,half_lenght);

	Vector2D top_right(half_lenght,-half_lenght);
	Vector2D top_left(-half_lenght,-half_lenght);


	Example::AssignmentApp::LineData dots; 

	dots.c1 = shape_colour;
	dots.c2 = shape_colour;

	//Right Side of Square
	dots.x1 = homogen_matrix.Tranformation(top_right).Get(0);
	dots.y1 = homogen_matrix.Tranformation(top_right).Get(1);
	dots.x2 = homogen_matrix.Tranformation(bottom_right).Get(0);
	dots.y2 = homogen_matrix.Tranformation(bottom_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Left side of Square
	dots.x1 = homogen_matrix.Tranformation(top_left).Get(0);
	dots.y1 = homogen_matrix.Tranformation(top_left).Get(1);
	dots.x2 = homogen_matrix.Tranformation(bottom_left).Get(0);
	dots.y2 = homogen_matrix.Tranformation(bottom_left).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Bottom of Square
	dots.x1 = homogen_matrix.Tranformation(bottom_left).Get(0);
	dots.y1 = homogen_matrix.Tranformation(bottom_left).Get(1);
	dots.x2 = homogen_matrix.Tranformation(bottom_right).Get(0);
	dots.y2 = homogen_matrix.Tranformation(bottom_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Top of Square
	dots.x1 = homogen_matrix.Tranformation(top_left).Get(0);
	dots.y1 = homogen_matrix.Tranformation(top_left).Get(1);
	dots.x2 = homogen_matrix.Tranformation(top_right).Get(0);
	dots.y2 = homogen_matrix.Tranformation(top_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);
}

float Square::Get_Size()
{
	return lenght_side/2;
}