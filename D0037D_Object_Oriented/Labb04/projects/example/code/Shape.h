#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Vector_Matrix.h"
#include "assignmentapp.h"



class Shape 
{

	public:

		virtual void Set_Pos(float x, float y);
		virtual void Render() = 0;
		void Set_Colour(float r, float b, float g);
		void Set_Rotation(float degree);


	protected:
		Vector2D pos;
		Matrix2D rotation;
		Example::AssignmentApp::Colour shape_colour;
};

class Square:public Shape
{


	public:
		Square(float lenght);
		~Square();
		void Set_Pos(float x, float y);
		void Render();

	private:
		float lenght_side;

};

class Triangle :public Shape
{


	public:    
		Triangle(float b, float h);
		~Triangle();
		void Set_Pos(float x, float y);
		void Render();

	private:
		float base, height;
};

class Circle : public Shape
{

	public:
		Circle(float rad);
		~Circle();
		void Set_Pos(float x, float y);
		void Render();

	private:
		float radius;

};

#endif // !SHAPE_H