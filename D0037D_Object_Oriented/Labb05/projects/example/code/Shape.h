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
		virtual float Get(int index) = 0;
		virtual float Get_Size() = 0;
		void Set_Colour(float r, float b, float g);
		void Set_Rotation(float degree);
		void Set_Velocity(float vel_x, float vel_y);
		Vector2D Get_Position();
		Vector2D Get_Velocity();
		void Add_Velocity(const Vector2D& other);
		float Get_Radius();
		Vector2D Collision();
		Vector2D Reflection();
		Vector2D Shape_Reflection(Shape& other);
		void Update();

		Vector2D velocity;
		
	protected:
		Matrix2D homogen_matrix; 
		Example::AssignmentApp::Colour shape_colour;
};

class Square: public Shape
{
	public:
		Square(float lenght);
		~Square();
		void Set_Pos(float x, float y);
		float Get(int index);
		void Render();
		float Get_Size();

	private:
		float lenght_side;
};

class Triangle :public Shape
{
	public:    
		Triangle(float b, float h);
		~Triangle();
		void Set_Pos(float x, float y);
		float Get(int index);
		void Render();
		float Get_Size();
	private:
		float base, height;
};

class Circle : public Shape
{
	public:
		Circle(float rad);
		Circle();
		~Circle();
		void Set_Pos(float x, float y);
		float Get(int index);
		void Render();
		bool Collision(Shape& other);
		float Get_Size();

	protected:
		float radius;
};

#endif // !SHAPE_H