#include "Shape.h"
#pragma once

Triangle::Triangle(float b, float h)
{
	base = b;
	height = h;

}


void Triangle::Set_Pos(float x, float y)
{
	pos.coordinates[0] = x;
	pos.coordinates[1] = y;
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

	dots.x1 = pos.coordinates[0] + rotation.Tranformation(bottom_left).Get(0);
	dots.y1 = pos.coordinates[1] + rotation.Tranformation(bottom_left).Get(1);
	dots.x2 = pos.coordinates[0] + rotation.Tranformation(bottom_right).Get(0);
	dots.y2 = pos.coordinates[1] + rotation.Tranformation(bottom_right).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	////Left side of Triangle

	dots.x1 = pos.coordinates[0] + rotation.Tranformation(bottom_left).Get(0);
	dots.y1 = pos.coordinates[1] + rotation.Tranformation(bottom_left).Get(1);
	dots.x2 = pos.coordinates[0] + rotation.Tranformation(top).Get(0);
	dots.y2 = pos.coordinates[1] + rotation.Tranformation(top).Get(1);
	Example::AssignmentApp::DrawLine(dots);

	//Right side of Triangle

	dots.x1 = pos.coordinates[0] + rotation.Tranformation(bottom_right).Get(0);
	dots.y1 = pos.coordinates[1] + rotation.Tranformation(bottom_right).Get(1);
	dots.x2 = pos.coordinates[0] + rotation.Tranformation(top).Get(0);
	dots.y2 = pos.coordinates[1] + rotation.Tranformation(top).Get(1);
	Example::AssignmentApp::DrawLine(dots);
}