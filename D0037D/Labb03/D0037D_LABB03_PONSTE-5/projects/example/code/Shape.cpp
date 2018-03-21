#include "Shape.h"
#include <iostream>
#pragma once


void Shape::Set_Pos(float x, float y)
{
	pos.coordinates[0] = x;
	pos.coordinates[1] = y;
}


//funktion to set color to the shape
void Shape::Set_Colour(float r ,float g, float b)
{
	shape_colour.r = r;
	shape_colour.g = g;
	shape_colour.b = b;
}

void Shape::Set_Rotation(float degree)
{
	rotation = Matrix2D::Rotation(degree);

}