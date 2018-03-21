#include "Shape.h"
#include <iostream>
#pragma once


void Shape::Set_Pos(float x, float y)
{
	homogen_matrix.matrix[0][2] = x;
	homogen_matrix.matrix[1][2] = y;
}


//funktion to set color to the shape
void Shape::Set_Colour(float r ,float g, float b)
{
	shape_colour.r = r;
	shape_colour.g = g;
	shape_colour.b = b;
}

Vector2D Shape::Get_Position()
{
	Vector2D new_vector;
	new_vector.coordinates[0] = this->homogen_matrix.matrix[0][2];
	new_vector.coordinates[1] = this->homogen_matrix.matrix[1][2];
	return new_vector;
}

void Shape::Set_Rotation(float degree)
{
	Vector2D pos = this->Get_Position();
	homogen_matrix = Matrix2D::Rotation(degree);
	homogen_matrix += pos;
}

void Shape::Set_Velocity(float vel_x,float vel_y)
{
	velocity.Set(vel_x,vel_y);
}

Vector2D Shape::Get_Velocity()
{
	return velocity;
}

void Shape::Add_Velocity(const Vector2D& other)
{
	homogen_matrix += velocity;
}

Vector2D Shape::Reflection()
{
	Vector2D normal_right(-1,0);
	Vector2D normal_left(1,0);
	Vector2D normal_top(0,-1);
	Vector2D normal_bottom(0,1);
	Vector2D reflection = velocity;
	
	if (velocity.Get(0) > 0 && homogen_matrix.matrix[0][2] >=1)
	{
		reflection = velocity - (normal_right*(2*normal_right.DotProduct(velocity)));
	}
	else if(velocity.Get(0) < 0 && homogen_matrix.matrix[0][2] <=-1)
	{
		reflection = velocity - (normal_left*(2*normal_left.DotProduct(velocity)));
	}


	if (velocity.Get(1) > 0 && homogen_matrix.matrix[1][2] >=1)
	{
		reflection = velocity - (normal_top*(2*normal_top.DotProduct(velocity)));
	}
	else if(velocity.Get(1) < 0 && homogen_matrix.matrix[1][2] <=-1)
	{
		reflection = velocity - (normal_bottom*(2*normal_bottom.DotProduct(velocity)));
	}
	return reflection;
}

Vector2D Shape::Shape_Reflection(Shape& other)
{
	Vector2D normal_right(-1,0);
	Vector2D normal_left(1,0);
	Vector2D normal_top(0,-1);
	Vector2D normal_bottom(0,1);
	Vector2D reflection = velocity;

	if (velocity.Get(0) > 0 && other.Get_Position().Get(0) >= this->Get_Position().Get(0))
	{
		reflection = velocity - (normal_right*(2*normal_right.DotProduct(velocity)));
	}
	else if(velocity.Get(0) < 0 && other.Get_Position().Get(0) <= this->Get_Position().Get(0))
	{
		reflection = velocity - (normal_left*(2*normal_left.DotProduct(velocity)));
	}

	if (velocity.Get(1) > 0 && other.Get_Position().Get(1) >= this->Get_Position().Get(1))
	{
		reflection = velocity - (normal_top*(2*normal_top.DotProduct(velocity)));
	}
	else if(velocity.Get(1) < 0 && other.Get_Position().Get(1) <= this->Get_Position().Get(1))
	{
		reflection = velocity - (normal_bottom*(2*normal_bottom.DotProduct(velocity)));
	}
	return reflection;
}

void Shape::Update()
{
	velocity = this->Reflection();
	this->Add_Velocity(velocity);
}

