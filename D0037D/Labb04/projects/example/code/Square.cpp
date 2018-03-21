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
	pos.coordinates[0] = x;
	pos.coordinates[1] = y;
	
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
	dots.x1 = pos.coordinates[0] + rotation.Tranformation(top_right).Get(0);
	dots.y1 = pos.coordinates[1] + rotation.Tranformation(top_right).Get(1);
	dots.x2 = pos.coordinates[0] + rotation.Tranformation(bottom_right).Get(0);
	dots.y2 = pos.coordinates[1] + rotation.Tranformation(bottom_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Left side of Square
	dots.x1 = pos.coordinates[0] + rotation.Tranformation(top_left).Get(0);
	dots.y1 = pos.coordinates[1] + rotation.Tranformation(top_left).Get(1);
	dots.x2 = pos.coordinates[0] + rotation.Tranformation(bottom_left).Get(0);
	dots.y2 = pos.coordinates[1] + rotation.Tranformation(bottom_left).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Bottom of Square
	dots.x1 = pos.coordinates[0] + rotation.Tranformation(bottom_left).Get(0);
	dots.y1 = pos.coordinates[1] + rotation.Tranformation(bottom_left).Get(1);
	dots.x2 = pos.coordinates[0] + rotation.Tranformation(bottom_right).Get(0);
	dots.y2 = pos.coordinates[1] + rotation.Tranformation(bottom_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Top of Square
	dots.x1 = pos.coordinates[0] + rotation.Tranformation(top_left).Get(0);
	dots.y1 = pos.coordinates[1] + rotation.Tranformation(top_left).Get(1);
	dots.x2 = pos.coordinates[0] + rotation.Tranformation(top_right).Get(0);
	dots.y2 = pos.coordinates[1] + rotation.Tranformation(top_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);
	
}

