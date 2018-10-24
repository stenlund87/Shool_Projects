#include "Vector_Matrix.h"


Matrix2D::Matrix2D()
{
    matrix[0][0] = 1;
    matrix[0][1] = 0;
	matrix[0][2] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 1;
	matrix[1][2] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

Matrix2D::Matrix2D(const Matrix2D& original)
{
	int r, k;
	for (r = 0; r<3; r++)
		for (k = 0; k<3; k++)
			 matrix[r][k] = original.matrix[r][k];
}

Matrix2D::Matrix2D(float a, float b, float c, float d)
{
    matrix[0][0] = a;
    matrix[0][1] = b;
    matrix[1][0] = c;
    matrix[1][1] = d;
}

float Matrix2D::Get(int row, int col)
{
	if(row<=2 && row>=0 && col<=2 && col>=0)
		return matrix[row][col];
	else
		throw "Index out of bounds!";
}



void Matrix2D::Set(int row, int col, float value)
{
	if(row<=1 && row>=0 && col<=1 && col>=0)
		matrix[row][col] = value;
	else
		throw "Index out of bounds!";
}

void Matrix2D::Set_Position(const Vector2D& pos)
{
	this->matrix[0][2] = pos.coordinates[0];
	this->matrix[1][2] = pos.coordinates[1];
}

Matrix2D Matrix2D::Transpose()
{
	Matrix2D new_object;
	int r, k;
	for (r = 0; r<3; r++)
		for (k = 0; k<3; k++)
			new_object.matrix[k][r] = matrix[r][k];
	return new_object;
}

Matrix2D Matrix2D::Rotation(float degree)
{
	Matrix2D new_object;
	degree = degree*3.14592/180;
	new_object.matrix[0][0] = cos(degree);
	new_object.matrix[0][1] = -sin(degree);
	new_object.matrix[1][0] = sin(degree);
	new_object.matrix[1][1] = cos(degree);
	return new_object;
}

Vector2D Matrix2D::Tranformation(const Vector2D& vector)
{
	Vector2D new_object;
	new_object.coordinates[0] = matrix[0][0] * vector.coordinates[0] + matrix[0][1]*vector.coordinates[1] + matrix[0][2]*vector.coordinates[2];
	new_object.coordinates[1] = matrix[1][0] * vector.coordinates[0] + matrix[1][1]*vector.coordinates[1] + matrix[1][2]*vector.coordinates[2];
	new_object.coordinates[2] = matrix[2][0] * vector.coordinates[0] + matrix[2][1]*vector.coordinates[1] + matrix[2][2]*vector.coordinates[2];
	return new_object;
}


Matrix2D Matrix2D::TranslationMatrix(const Vector2D& other)
{
	Matrix2D new_matrix;
	new_matrix.matrix[0][0] = 1;
    new_matrix.matrix[0][1] = 0;
	new_matrix.matrix[0][2] = other.Get(0);

	new_matrix.matrix[1][0] = 0;
	new_matrix.matrix[1][1] = 1;
	new_matrix.matrix[1][2] = other.Get(1);

	new_matrix.matrix[2][0] = 0;
	new_matrix.matrix[2][1] = 0;
	new_matrix.matrix[2][2] = 1;

	return new_matrix;
}

Matrix2D& Matrix2D::operator+=(const Vector2D& other)
{
	this->matrix[0][2] += other.coordinates[0];
	this->matrix[1][2] += other.coordinates[1];
	return *this;
}

Matrix2D Matrix2D::operator*(const Matrix2D& other)
{
	Matrix2D new_object;
	int r, k;
	for (r = 0; r<3; r++)
	{
		for (k = 0; k<3; k++)
			new_object.matrix[r][k] = this->matrix[r][k] * other.matrix[r][k];
	}
	return new_object;
}
Matrix2D& Matrix2D::operator=(const Matrix2D& other)
{
	int r, k;
	for (r = 0; r<3; r++)
	{
		for (k = 0; k<3; k++)
			 this->matrix[r][k] = other.matrix[r][k];
	}
	return *this;
}

