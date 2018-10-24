#include <array>
#include "Vector_Matrix.h"
using namespace std;


 //konstruktor när man skickar in argument
Vector2D::Vector2D(float x, float y)	
{
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = 1;
}


//konstruktor när man vill skapa ett object utan att skicka in argument
Vector2D::Vector2D() 
{
	coordinates[0] = 0;
	coordinates[1] = 0;
	coordinates[2] = 1;
}

Vector2D::Vector2D(const Vector2D& other)
{
	this->coordinates[0] = other.coordinates[0];
	this->coordinates[1] = other.coordinates[1];
	this->coordinates[2] = other.coordinates[2];
}

//Adderar värderna från objectet man skickar in som argument
 void Vector2D::Addition(const Vector2D& other)
{
	this->coordinates[0] =  this->coordinates[0] + other.coordinates[0];
	this->coordinates[1] =  this->coordinates[1] + other.coordinates[1]; 
}

void Vector2D::Substract(const Vector2D& other)
{
	this->coordinates[0] =  this->coordinates[0] - other.coordinates[0];
	this->coordinates[1] =  this->coordinates[1] - other.coordinates[1];
}

Vector2D Vector2D::Mulitplication(float number)
{
	this->coordinates[0] = this->coordinates[0] * number;
	this->coordinates[1] = this->coordinates[1] * number;
	return *this;
}
 
float Vector2D::Get(int indx) const
{
	if(indx<=2 && indx>=0)
		return coordinates[indx];
	else
		throw "Index out of bounds";
}


void Vector2D::Set(float x,float y)
{
	coordinates[0] = x;
	coordinates[1] = y;
}


//Beräknar skalärprodukten av två vektorer
float Vector2D::DotProduct(const Vector2D& other)
{
	float product;
	product = this->coordinates[0] * other.coordinates[0] + this->coordinates[1] * other.coordinates[1];
	return product;
}


//Beräknar längden av vektorn
float Vector2D::Length()
{
	float length;
	length = coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1];	
	length = sqrt(length);
	return length;
}

void Vector2D::Normalizing()
{
	float length,u,v;
	length = Length();
	v = coordinates[0]/length;
	u = coordinates[1]/length;
	coordinates[0] = v;
	coordinates[1] = u;
}

//Overloadar operatorn + så att ett nytt objekt av samma klass skapas med de sammanslagna värderna
Vector2D Vector2D::operator+(Vector2D& other)
{
	Vector2D new_object;
	new_object.coordinates[0] = this->coordinates[0] + other.coordinates[0];
	new_object.coordinates[1] = this->coordinates[1] + other.coordinates[1]; 
	new_object.coordinates[2] = 1;
	return new_object;
}

Vector2D Vector2D::operator+(float number)
{
	this->coordinates[0] = this->coordinates[0] + number;
	this->coordinates[1] = this->coordinates[1] + number;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	Vector2D new_object;
	new_object.coordinates[0] = this->coordinates[0] - other.coordinates[0];
	new_object.coordinates[1] = this->coordinates[1] - other.coordinates[1];
	new_object.coordinates[2] = 1;
	return new_object;
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
	this->coordinates[0] = other.coordinates[0];
	this->coordinates[1] = other.coordinates[1];
	this->coordinates[2] = other.coordinates[2];
	return *this;
}

Vector2D Vector2D::operator*(const Vector2D& other)
{
	Vector2D new_object;
	new_object.coordinates[0] = this->coordinates[0] * other.coordinates[0];
	new_object.coordinates[1] = this->coordinates[1] * other.coordinates[1];
	new_object.coordinates[2] = 1;
	return new_object;
}

Vector2D Vector2D::operator*(float number)
{
	return this->Mulitplication(number);
}

bool Vector2D::operator==(const Vector2D& other)
{
	return (this->coordinates[0] == other.coordinates[0] && this->coordinates[1] == other.coordinates[1]);
}

bool Vector2D::operator!=(const Vector2D& other)
{
	return (this->coordinates[0] != other.coordinates[0] || this->coordinates[1] != other.coordinates[1]);
}
