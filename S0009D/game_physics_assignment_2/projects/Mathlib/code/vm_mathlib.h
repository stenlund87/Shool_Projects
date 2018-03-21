#ifndef VM_MATHLIB
#define VM_MATHLIB

#include <array>
#include <exception>
#include <iostream>
#include <math.h>


class Vector4D
{
public:
	friend class Matrix4D;

	/**
	*Constructor for setting position
	*@param floats x-z
	*/
	Vector4D(float x, float y, float z);


	/**
	*Constructor for setting position
	*@param floats x-w
	*/
	Vector4D(float x, float y, float z, float w);

	/**
	*Default constructor, all coordinates are set to 0
	*/
	Vector4D();

	/**
	*Constructor for copying a Vector4D object
	*@param other, an object of type Vector4D
	*/
	Vector4D(const Vector4D& other);

	/**
	*Method to get the position of the index
	*@param int index (0-3)
	*/
	float Get(int indx) const;

	float* GetVector();

	/**
	*Method to set the position of the vector
	*@param float (x-z)
	*/
	void Set(float x, float y, float z);

	/**
	*Method to add the values of another Vector4D to the object that calls the function
	*@param other, an object of type Vector4D
	*/
	void Addition(const Vector4D& other);

	/**
	*Method to subtract the values of another Vector4D to the object that calls the function
	**@param other, an object of type Vector4D
	*/
	void Substract(const Vector4D& other);

	/**
	*Method to calculate the crossproduct
	*@param other, an object of type Vector4D
	*@return a new Vector4D object
	*/
	Vector4D CrossProduct(const Vector4D& other);

	/**
	*Methodto calculate the lenght of the vector
	*@return the lenght
	*/
	float Length();

	/**
	*Method to normalize the vector
	*/
	Vector4D Normalize();

    Vector4D CalculateNormal(Vector4D v0, Vector4D v1, Vector4D v2);

	//Overloaded operators
	Vector4D operator+(const Vector4D& other); //overload on + and creates a new object of Vector4D
	Vector4D operator+(float number); //Overload on + and changes the values inside the Vector4D
	Vector4D operator-(const Vector4D& other); //Overload on - and creates a new object of Vector4D
	Vector4D& operator=(const Vector4D& other); //Overloadon = and creates a new object of Vector4D
	float operator*(const Vector4D& other); //Overload on * for DotProduct
	Vector4D operator*(float number); //Overload for scaling
	bool operator==(const Vector4D& other);
	bool operator!=(const Vector4D& other);
	float& operator[](int index); //Overload for getting the value in the array, you may change the value
	Vector4D operator/(float num);
    Vector4D operator/(Vector4D &other);
	float coordinates[4];

};


//Constructor 
inline
Vector4D::Vector4D(float x, float y, float z)
{
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;
	coordinates[3] = 1;
}

inline
Vector4D::Vector4D(float x, float y, float z, float w)
{
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;
	coordinates[3] = w;
}

inline
//konstruktor n�r man vill skapa ett object utan att skicka in argument
Vector4D::Vector4D()
{
	coordinates[0] = 0;
	coordinates[1] = 0;
	coordinates[2] = 0;
	coordinates[3] = 1;
}

inline
Vector4D::Vector4D(const Vector4D& other)
{
	for (int i = 0; i < 4; i++)
	{
		this->coordinates[i] = other.coordinates[i];
	}
}

//Adderar v�rderna fr�n objectet man skickar in som argument
inline void Vector4D::Addition(const Vector4D& other)
{
    this->coordinates[0] = this->coordinates[0] + other.coordinates[0];
	this->coordinates[1] = this->coordinates[1] + other.coordinates[1];
	this->coordinates[2] = this->coordinates[2] + other.coordinates[2];
}

inline void Vector4D::Substract(const Vector4D& other)
{
	this->coordinates[0] = this->coordinates[0] - other.coordinates[0];
	this->coordinates[1] = this->coordinates[1] - other.coordinates[1];
	this->coordinates[2] = this->coordinates[2] - other.coordinates[2];
}

inline float Vector4D::Get(int indx) const
{
	if (indx <= 3 && indx >= 0)
		return coordinates[indx];
	else
		throw "Index out of bounds";
}

inline float* Vector4D::GetVector()
{
	return (float*)coordinates;
}

inline void Vector4D::Set(float x, float y, float z)
{
	this->coordinates[0] = x;
	this->coordinates[1] = y;
	this->coordinates[2] = z;
}

inline
Vector4D Vector4D::CrossProduct(const Vector4D& other)
{
	Vector4D new_object;
	new_object.coordinates[0] = this->coordinates[1] * other.coordinates[2] - this->coordinates[2] * other.coordinates[1];
	new_object.coordinates[1] = this->coordinates[2] * other.coordinates[0] - this->coordinates[0] * other.coordinates[2];
	new_object.coordinates[2] = this->coordinates[0] * other.coordinates[1] - this->coordinates[1] * other.coordinates[0];
	new_object.coordinates[3] = 1;
	return new_object;
}

//Ber�knar l�ngden av vektorn
inline float Vector4D::Length()
{
	float length;
	length = coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1] + coordinates[2] * coordinates[2];
	length = sqrt(length);
	return length;
}

inline Vector4D Vector4D::Normalize()
{
    Vector4D normal;
	float length, u, v, w;
	if(Length() > 0) //<< If length is 0, all coordinates are 0
	{
		length = 1.0f / Length();
		normal.coordinates[0] = this->coordinates[0] * length;
		normal.coordinates[1] = this->coordinates[1] * length;
		normal.coordinates[2] = this->coordinates[2] * length;
        return normal;
	}
}


inline
Vector4D Vector4D::CalculateNormal(Vector4D v0, Vector4D v1, Vector4D v2)
{
    Vector4D normal;
    Vector4D u = v1 - v0;
    Vector4D v = v2 - v0;
    Vector4D dir = u.CrossProduct(v);
    normal = dir/dir.Length();
    return normal;

}

//Overloadar operatorn + s� att ett nytt objekt av samma klass skapas med de sammanslagna v�rderna
inline Vector4D Vector4D::operator+(const Vector4D& other)
{
	Vector4D new_object;
	new_object.coordinates[0] = this->coordinates[0] + other.coordinates[0];
	new_object.coordinates[1] = this->coordinates[1] + other.coordinates[1];
	new_object.coordinates[2] = this->coordinates[2] + other.coordinates[2];
	new_object.coordinates[3] = 1;
	return new_object;
}

inline Vector4D Vector4D::operator+(float number)
{
    Vector4D newVector;
    newVector.coordinates[0] = this->coordinates[0] + number;
    newVector.coordinates[1] = this->coordinates[1] + number;
    newVector.coordinates[2] = this->coordinates[2] + number;
	return newVector;
}

inline Vector4D Vector4D::operator-(const Vector4D& other)
{
	Vector4D new_object;
	new_object.coordinates[0] = this->coordinates[0] - other.coordinates[0];
	new_object.coordinates[1] = this->coordinates[1] - other.coordinates[1];
	new_object.coordinates[2] = this->coordinates[2] - other.coordinates[2];
	new_object.coordinates[3] = 1;
	return new_object;
}

inline Vector4D& Vector4D::operator=(const Vector4D& other)
{
	this->coordinates[0] = other.coordinates[0];
	this->coordinates[1] = other.coordinates[1];
	this->coordinates[2] = other.coordinates[2];
	this->coordinates[3] = other.coordinates[3];
	return *this;
}

inline float Vector4D::operator*(const Vector4D& other)
{
	float product;
	product = this->coordinates[0] * other.coordinates[0] + this->coordinates[1] * other.coordinates[1] + this->coordinates[2] * other.coordinates[2];
	return product;
}

inline Vector4D Vector4D::operator*(float number)
{
    Vector4D newVector;
    newVector.coordinates[0] = this->coordinates[0] * number;
    newVector.coordinates[1] = this->coordinates[1] * number;
    newVector.coordinates[2] = this->coordinates[2] * number;
    return newVector;
}

inline bool Vector4D::operator==(const Vector4D& other)
{
	return (this->coordinates[0] == other.coordinates[0] && this->coordinates[1] == other.coordinates[1] && this->coordinates[2] == other.coordinates[2] != other.coordinates[3]);
}

inline bool Vector4D::operator!=(const Vector4D& other)
{
	return (this->coordinates[0] != other.coordinates[0] || this->coordinates[1] != other.coordinates[1] || this->coordinates[2] != other.coordinates[2] != other.coordinates[3]);
}

inline float& Vector4D::operator[](int index)
{
	return coordinates[index];
}

inline Vector4D Vector4D::operator/(float num)
{
	Vector4D newVector;
	newVector.coordinates[0] = this->coordinates[0] / num;
	newVector.coordinates[1] = this->coordinates[1] / num;
	newVector.coordinates[2] = this->coordinates[2] / num;
	return newVector;
}

inline Vector4D Vector4D::operator/(Vector4D &other)
{
    Vector4D newVector;
    newVector.coordinates[0] = this->coordinates[0] / other[0];
    newVector.coordinates[1] = this->coordinates[1] / other[1];
    newVector.coordinates[2] = this->coordinates[2] / other[2];
    return newVector;
}

class Matrix4D
{
public:
	friend class Vector4D;

	/**Constructor of an identity matrix
	*/
	Matrix4D();

	/**
	*Constructor for copying an Matrix4D object
	*@param an Matrix4D object
	*/
	Matrix4D(const Matrix4D& original);

	/**
	*Constructor when the user sends in values to the matrix (values fills in like a 3x3 Matrix)
	*@param floats a-i
	*/
	Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i);

	/**
	*Constructor when the user sends in all values to the matrix
	*@param floats a-i
	*/
	Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
	float* getMatrix() { return *matrix; }
	~Matrix4D();

	/**
	*Returns the value from the row and column
	*@param row, index (0-2)
	*@param col, index (0-2)
	*@returns value of position
	*/
	float Get(int row, int col);

    /**
     * Method that returns the matrix location
     * @return Vector4D
     * */
    Vector4D GetPosition();

	/**
	*Changes the value of the position (row,col)
	*@param row index of the matrix
	*@param col index of the matrix
	*@param value, float
	*@returns the matrix
	*/
	void Set(int row, int col, float value);

	/**
	*Sets the position of the Matrix4D to that of the Vector4D
	*@param an Vector4D object
	*/
	void Set_Position(const Vector4D& other);

	/**
	*Sets the position of the Matrix4D to that of the Vector4D
	*@param float x, float y, float z
	*/
	void Set_Position(float x, float y, float z);

	/**
	*Transposes the matrix
	*@returns a new Matrix4D that is transposed from the object that calls the method
	*/
	Matrix4D Transpose();

	/**
	* Return a matrix for rotating around x-position, given number of degrees.
	*@param other, a Vector4D object;
	* @param degree, Degrees in radians.
	* @return Rotation matrix.
	*/
	static Matrix4D Rotation_Vector(const Vector4D& other, float degree);

	/**
	* Return a matrix for rotating around x-position, given number of degrees.
	* @param degree, Degrees in radians.
	* @return Rotation matrix.
	*/
	static Matrix4D Rotation_X(float degree);

	/**
	* Return a matrix for rotating around y-position, given number of degrees.
	* @param degree, Degrees in radians.
	* @return Rotation matrix.
	*/
	static Matrix4D Rotation_Y(float degree);

	/**
	* Return a matrix for rotating around z-position, given number of degrees.
	* @param degree, Degrees in radians.
	* @return Rotation matrix.
	*/
	static Matrix4D Rotation_Z(float degree);

	/**
	*Return a new object of the class Matrix4D
	*@param an object of Vector4D
	*@return Translation matrix that contains rotation and position
	*/
	static Matrix4D TranslationMatrix(const Vector4D& other);

	/**
	*Return a new object of the class Vector4D.
	*@param an object of the class Vector4D.
	*@return Transformation vector
	*/
	Vector4D Transformation(const Vector4D& other);

	/**
	*Calculating the inverse for the matrix
	*@return a new object of Matrix4D
	*/
	Matrix4D Inverse();

	/**
	 * Calculate a projection matrix
	 * @param float aspect, window aspect eg. 4/3
	 * @param float near, when object should not render near the camera
	 * @param float far, distance from the camera when object should not render
	 * @param float top
	 * @param float bottom
	 * @param float right
	 * @param float left
	 * @return Matrix4D, projection matrix
	 * */
	Matrix4D Projection(float aspect, float near, float far,float top, float bottom ,float right,float left);

    Matrix4D Projection();
	/**
	 * View at function that returns a view matrix
	 * @param Vector4D eye, the eye vector
	 * @param Vector4D target, the taget direction?
	 * @param Vector4D up, vector that defines up axxis
	 * */
	Matrix4D LookAt(Vector4D eye, Vector4D target, Vector4D up);

    /**
     * Method that returns a skew matrix from given vector
     * @param Vector4D in, the vector that will define the skew matrix
     * @return Matrix4D skew matrix
     */
    Matrix4D Skew(Vector4D &in);

    Matrix4D InertiaTensorCube(Vector4D &extends, float mass);
    Matrix4D InertiaTensorCylinder(float mass, float radius, float height);

	/**
	*Adds the value of the vector to the last column of the matrix
	*/
	Matrix4D& operator+=(const Vector4D& other);

    Matrix4D operator+(const Matrix4D& other);

	/**
	*Overloaded operator for multiplication for two matrix
	*@return, a new object of type Matrix4D
	*/
	Matrix4D operator*(const Matrix4D& other);

    Matrix4D operator*(float val);

	/**
	*Overloaded operator for multiplication between matrix and vector
	*@return a new object of type Vector4D
	*/
	Vector4D operator*(const Vector4D& other);

	/**
	*Overloaded operator for copying a matrix;
	*/
	Matrix4D& operator=(const Matrix4D& other);

	/**
	*Overloaded operator for getting the value in the matrix;
	*/
	float* operator[](int val);

	Vector4D Multiply(Vector4D &other);

	float matrix[4][4];

};

inline
Matrix4D::Matrix4D()
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;

	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;


}

inline
Matrix4D::Matrix4D(const Matrix4D& original)
{
	int r, k;
	for (r = 0; r<4; r++)
		for (k = 0; k<4; k++)
			matrix[r][k] = original.matrix[r][k];
}

inline
Matrix4D::Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	matrix[0][0] = a;
	matrix[0][1] = b;
	matrix[0][2] = c;
	matrix[0][3] = 0;

	matrix[1][0] = d;
	matrix[1][1] = e;
	matrix[1][2] = f;
	matrix[1][3] = 0;

	matrix[2][0] = g;
	matrix[2][1] = h;
	matrix[2][2] = i;
	matrix[2][3] = 0;

	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;

}

inline
Matrix4D::Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	matrix[0][0] = a;
	matrix[0][1] = b;
	matrix[0][2] = c;
	matrix[0][3] = d;

	matrix[1][0] = e;
	matrix[1][1] = f;
	matrix[1][2] = g;
	matrix[1][3] = h;

	matrix[2][0] = i;
	matrix[2][1] = j;
	matrix[2][2] = k;
	matrix[2][3] = l;

	matrix[3][0] = m;
	matrix[3][1] = n;
	matrix[3][2] = o;
	matrix[3][3] = p;
}

inline
Matrix4D::~Matrix4D()
{
}


inline
Vector4D Matrix4D::GetPosition()
{
    return Vector4D(matrix[0][3], matrix[1][3], matrix[2][3]);
}

inline
void Matrix4D::Set_Position(const Vector4D& pos)
{
	this->matrix[0][3] = pos.coordinates[0];
	this->matrix[1][3] = pos.coordinates[1];
	this->matrix[2][3] = pos.coordinates[2];
}

inline
void Matrix4D::Set_Position(float x, float y, float z)
{
	this->matrix[0][3] = x;
	this->matrix[1][3] = y;
	this->matrix[2][3] = z;
}

inline
Matrix4D Matrix4D::Transpose()
{
	Matrix4D new_object;
	int r, k;
	for (r = 0; r<4; r++)
		for (k = 0; k<4; k++)
			new_object.matrix[k][r] = matrix[r][k];
	return new_object;
}

inline
Matrix4D Matrix4D::Rotation_Vector(const Vector4D& other, float degree)
{
	Matrix4D new_object;
	degree = degree*3.14592 / 180;
	float c = 0;
	float s = 0;
	c = cos(degree);
	s = sin(degree);
	new_object.matrix[0][0] = other.coordinates[0] * other.coordinates[0] + (1 - (other.coordinates[0] * other.coordinates[0]))*c;
	new_object.matrix[0][1] = other.coordinates[0] * other.coordinates[1] * (1 - c) - other.coordinates[0] * s;
	new_object.matrix[0][2] = other.coordinates[0] * other.coordinates[2] * (1 - c) + other.coordinates[1] * s;

	new_object.matrix[1][0] = other.coordinates[0] * other.coordinates[1] * (1 - c) + other.coordinates[2] * s;
	new_object.matrix[1][1] = other.coordinates[1] * other.coordinates[1] + (1 - (other.coordinates[1] * other.coordinates[1]))*c;
	new_object.matrix[1][2] = other.coordinates[0] * other.coordinates[2] * (1 - c) - other.coordinates[0] * s;

	new_object.matrix[2][0] = other.coordinates[0] * other.coordinates[2] * (1 - c) - other.coordinates[1] * s;
	new_object.matrix[2][1] = other.coordinates[1] * other.coordinates[2] * (1 - c) + other.coordinates[0] * s;
	new_object.matrix[2][2] = other.coordinates[2] * other.coordinates[2] + (1 - (other.coordinates[2] * other.coordinates[2]))*c;

	return new_object;
}

inline
Matrix4D Matrix4D::Rotation_X(float degree)
{
	Matrix4D new_object;
	degree = degree*3.14592 / 180;
	float c, s;
	c = cos(degree);
	s = sin(degree);
	new_object.matrix[1][1] = c;
	new_object.matrix[1][2] = -s;
	new_object.matrix[2][1] = s;
	new_object.matrix[2][2] = c;
	return new_object;
}

inline
Matrix4D Matrix4D::Rotation_Y(float degree)
{
	Matrix4D new_object;
	degree = degree*3.14592 / 180;
	float c, s;
	c = cos(degree);
	s = sin(degree);
	new_object.matrix[0][0] = c;
	new_object.matrix[0][2] = s;
	new_object.matrix[2][0] = -s;
	new_object.matrix[2][2] = c;
	return new_object;
}

inline
Matrix4D Matrix4D::Rotation_Z(float degree)
{
	Matrix4D new_object;
	degree = degree*3.14592 / 180;
	float c, s;
	c = cos(degree);
	s = sin(degree);
	new_object.matrix[0][0] = c;
	new_object.matrix[0][1] = -s;
	new_object.matrix[1][0] = s;
	new_object.matrix[1][1] = c;
	return new_object;
}

inline
Vector4D Matrix4D::Transformation(const Vector4D& vector)
{
	Vector4D new_object;
	new_object.coordinates[0] = matrix[0][0] * vector.coordinates[0] + matrix[0][1] * vector.coordinates[1] + matrix[0][2] * vector.coordinates[2];
	new_object.coordinates[1] = matrix[1][0] * vector.coordinates[0] + matrix[1][1] * vector.coordinates[1] + matrix[1][2] * vector.coordinates[2];
	new_object.coordinates[2] = matrix[2][0] * vector.coordinates[0] + matrix[2][1] * vector.coordinates[1] + matrix[2][2] * vector.coordinates[2];
	return new_object;
}


inline
Matrix4D Matrix4D::Inverse()
{
	Matrix4D new_object;
	float detA;
	float arr[16];

	try
	{
		//Calculating the determinant of the matrix
		detA = matrix[0][0] * matrix[1][1] * matrix[2][2] * matrix[3][3] + matrix[0][0] * matrix[1][2] * matrix[2][3] * matrix[3][1] + matrix[0][0] * matrix[1][3] * matrix[2][1] * matrix[3][2]
			+ matrix[0][1] * matrix[1][0] * matrix[2][3] * matrix[3][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] * matrix[3][3] + matrix[0][1] * matrix[1][3] * matrix[2][2] * matrix[3][0]
			+ matrix[0][2] * matrix[1][0] * matrix[2][1] * matrix[3][3] + matrix[0][2] * matrix[1][1] * matrix[2][3] * matrix[3][0] + matrix[0][2] * matrix[1][3] * matrix[2][0] * matrix[3][1]
			+ matrix[0][3] * matrix[1][0] * matrix[2][2] * matrix[3][1] + matrix[0][3] * matrix[1][1] * matrix[2][0] * matrix[3][2] + matrix[0][3] * matrix[1][2] * matrix[2][1] * matrix[3][0]
			- matrix[0][0] * matrix[1][1] * matrix[2][3] * matrix[3][2] - matrix[0][0] * matrix[1][2] * matrix[2][1] * matrix[3][3] - matrix[0][0] * matrix[1][3] * matrix[2][2] * matrix[3][1]
			- matrix[0][1] * matrix[1][0] * matrix[2][2] * matrix[3][3] - matrix[0][1] * matrix[1][2] * matrix[2][3] * matrix[3][0] - matrix[0][1] * matrix[1][3] * matrix[2][0] * matrix[3][2]
			- matrix[0][2] * matrix[1][0] * matrix[2][3] * matrix[3][1] - matrix[0][2] * matrix[1][1] * matrix[2][0] * matrix[3][3] - matrix[0][2] * matrix[1][3] * matrix[2][1] * matrix[3][0]
			- matrix[0][3] * matrix[1][0] * matrix[2][1] * matrix[3][2] - matrix[0][3] * matrix[1][1] * matrix[2][2] * matrix[3][0] - matrix[0][3] * matrix[1][2] * matrix[2][0] * matrix[3][1];

		//If the determinant is equal to 0, there exist no inverse of the matrix
		if (detA != 0)
		{
			arr[0] = matrix[1][1] * matrix[2][2] * matrix[3][3] + matrix[1][2] * matrix[2][3] * matrix[3][1] + matrix[1][3] * matrix[2][1] * matrix[3][2] - matrix[1][1] * matrix[2][3] * matrix[3][2] - matrix[1][2] * matrix[2][1] * matrix[3][3] - matrix[1][3] * matrix[2][2] * matrix[3][1];
			arr[1] = matrix[0][1] * matrix[2][3] * matrix[3][2] + matrix[0][2] * matrix[2][1] * matrix[3][3] + matrix[0][3] * matrix[2][2] * matrix[3][1] - matrix[0][1] * matrix[2][2] * matrix[3][3] - matrix[0][2] * matrix[2][3] * matrix[3][1] - matrix[0][3] * matrix[2][1] * matrix[3][2];
			arr[2] = matrix[0][1] * matrix[1][2] * matrix[3][3] + matrix[0][2] * matrix[1][3] * matrix[3][1] + matrix[0][3] * matrix[1][1] * matrix[3][2] - matrix[0][1] * matrix[1][3] * matrix[3][2] - matrix[0][2] * matrix[1][1] * matrix[3][3] - matrix[0][3] * matrix[1][2] * matrix[3][1];
			arr[3] = matrix[0][1] * matrix[1][3] * matrix[2][2] + matrix[0][2] * matrix[1][1] * matrix[2][3] + matrix[0][3] * matrix[1][2] * matrix[2][1] - matrix[0][1] * matrix[1][2] * matrix[2][3] - matrix[0][2] * matrix[1][3] * matrix[2][1] - matrix[0][3] * matrix[1][1] * matrix[2][2];

			arr[4] = matrix[1][0] * matrix[2][3] * matrix[3][2] + matrix[1][2] * matrix[2][0] * matrix[3][0] + matrix[1][3] * matrix[2][2] * matrix[3][0] - matrix[1][0] * matrix[2][2] * matrix[3][3] - matrix[1][2] * matrix[2][3] * matrix[3][0] - matrix[1][3] * matrix[2][0] * matrix[3][2];
			arr[5] = matrix[0][0] * matrix[2][2] * matrix[3][3] + matrix[0][2] * matrix[2][3] * matrix[3][0] + matrix[0][3] * matrix[2][0] * matrix[3][2] - matrix[0][0] * matrix[2][3] * matrix[3][2] - matrix[0][2] * matrix[2][0] * matrix[3][3] - matrix[0][3] * matrix[2][2] * matrix[3][0];
			arr[6] = matrix[0][0] * matrix[1][3] * matrix[3][2] + matrix[0][2] * matrix[1][0] * matrix[3][3] + matrix[0][3] * matrix[1][2] * matrix[3][0] - matrix[0][0] * matrix[1][2] * matrix[3][3] - matrix[0][2] * matrix[1][3] * matrix[3][0] - matrix[0][3] * matrix[1][0] * matrix[3][2];
			arr[7] = matrix[0][0] * matrix[1][2] * matrix[2][3] + matrix[0][2] * matrix[1][3] * matrix[2][0] + matrix[0][3] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][3] * matrix[2][2] - matrix[0][2] * matrix[1][0] * matrix[2][3] - matrix[0][3] * matrix[1][2] * matrix[2][0];

			arr[8] = matrix[1][0] * matrix[2][1] * matrix[3][3] + matrix[1][1] * matrix[2][3] * matrix[3][0] + matrix[1][3] * matrix[2][0] * matrix[3][1] - matrix[1][0] * matrix[2][3] * matrix[3][1] - matrix[1][1] * matrix[2][0] * matrix[3][3] - matrix[1][3] * matrix[2][1] * matrix[3][0];
			arr[9] = matrix[0][0] * matrix[2][3] * matrix[3][1] + matrix[0][1] * matrix[2][0] * matrix[3][3] + matrix[0][3] * matrix[2][1] * matrix[3][0] - matrix[0][0] * matrix[2][1] * matrix[3][3] - matrix[0][1] * matrix[2][3] * matrix[3][0] - matrix[0][3] * matrix[2][0] * matrix[3][1];
			arr[10] = matrix[0][0] * matrix[1][1] * matrix[3][3] + matrix[0][1] * matrix[1][3] * matrix[3][0] + matrix[0][3] * matrix[1][0] * matrix[3][1] - matrix[0][0] * matrix[1][3] * matrix[3][1] - matrix[0][1] * matrix[1][0] * matrix[3][3] - matrix[0][3] * matrix[1][1] * matrix[3][0];
			arr[11] = matrix[0][0] * matrix[1][3] * matrix[2][1] + matrix[0][1] * matrix[1][0] * matrix[2][3] + matrix[0][3] * matrix[1][1] * matrix[2][0] - matrix[0][0] * matrix[1][1] * matrix[2][3] - matrix[0][1] * matrix[1][3] * matrix[2][0] - matrix[0][3] * matrix[1][0] * matrix[2][1];

			arr[12] = matrix[1][0] * matrix[2][2] * matrix[3][1] + matrix[1][1] * matrix[2][0] * matrix[3][2] + matrix[1][2] * matrix[2][1] * matrix[3][0] - matrix[1][0] * matrix[2][1] * matrix[3][2] - matrix[1][1] * matrix[2][2] * matrix[3][0] - matrix[1][2] * matrix[2][0] * matrix[3][1];
			arr[13] = matrix[0][0] * matrix[2][1] * matrix[3][2] + matrix[0][1] * matrix[2][2] * matrix[3][0] + matrix[0][2] * matrix[2][0] * matrix[3][1] - matrix[0][0] * matrix[2][2] * matrix[3][1] - matrix[0][1] * matrix[2][0] * matrix[3][2] - matrix[0][2] * matrix[2][1] * matrix[3][0];
			arr[14] = matrix[0][0] * matrix[1][2] * matrix[3][1] + matrix[0][1] * matrix[1][0] * matrix[3][2] + matrix[0][2] * matrix[1][1] * matrix[3][0] - matrix[0][0] * matrix[1][1] * matrix[3][2] - matrix[0][1] * matrix[1][2] * matrix[3][0] - matrix[0][2] * matrix[1][0] * matrix[3][1];
			arr[15] = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][0] * matrix[1][2] * matrix[2][1] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][2] * matrix[1][1] * matrix[2][0];

			detA = 1.0f / detA;
			int i = 0;
			for (int r = 0; r < 4;r++)
			{
				for (int k = 0; k < 4;k++)
				{
					new_object[r][k] = detA*arr[i];
					i++;
				}
			}
			return new_object;

		}

		throw detA;
	}

	catch (float det)
	{
		std::cout << "There exist no inverse for the matrix" << std::endl;
	}
}

inline
Matrix4D Matrix4D::Projection(float aspect, float near, float far, float top, float bottom, float right, float left)
{
	Matrix4D proj;
	float rl = 1.0f/(right-left);
	float tb = 1.0f/(top-bottom);
	proj.matrix[0][0] = (2*near)*rl;
	proj.matrix[0][1] = 0;
	proj.matrix[0][2] = -(right+left) *rl;
	proj.matrix[0][3] = 0;

	proj.matrix[1][0] = 0;
	proj.matrix[1][1] = (2*near)*tb;
	proj.matrix[1][2] = (top+bottom)*tb;
	proj.matrix[1][3] = 0;

	proj.matrix[2][0] = 0;
	proj.matrix[2][1] = 0;
	proj.matrix[2][2] = -((far+near)/(far-near));
	proj.matrix[2][3] = -((2*far*near)/(far-near));

	proj.matrix[3][0] = 0;
	proj.matrix[3][1] = 0;
	proj.matrix[3][2] = -1.0;
	proj.matrix[3][3] = 0;

	return proj;
}

inline
Matrix4D Matrix4D::Projection()
{
    float fov = 60.0f;        //Field of view
    float near = 0.001f;        //Near clipping plane
    float far = 100.0f;        //Far clipping plane
    float S = 1 / (tan((fov / 2.0f) * (M_PI / 180.0f)));
    Matrix4D w_projArr =
            {
                    S,    0,    0,    0,
                    0,    S,    0,    0,
                    0,    0,    -1 * (far / (far - near)),    -1 * ((far * near) / (far - near)),
                    0,    0,    -1,    0
            };
    return w_projArr;
}

inline
Matrix4D Matrix4D::LookAt(Vector4D eye, Vector4D target, Vector4D up)
{
	Vector4D zAxis = (eye-target).Normalize(); //<< Forward vector

	Vector4D xAxis = (up.CrossProduct(zAxis)).Normalize(); //<< The right vector

	Vector4D yAxis = (zAxis.CrossProduct(xAxis)).Normalize();

	Matrix4D view(
			xAxis.coordinates[0], yAxis.coordinates[0], zAxis.coordinates[0], -(xAxis*eye),
			xAxis.coordinates[1], yAxis.coordinates[1], zAxis.coordinates[1], -(yAxis*eye),
			xAxis.coordinates[2], yAxis.coordinates[2], zAxis.coordinates[2], -(zAxis*eye),
		    0	,    0  , 	0	,  	  1      	);
	return view;
}

inline
Matrix4D Matrix4D::Skew(Vector4D &in)
{
    Matrix4D skewMatrix;
    skewMatrix[0][0] = 0;
    skewMatrix[0][1] = -in[2]; //<< -Az
    skewMatrix[0][2] = in[1]; //<< Ay
    skewMatrix[0][3] = 0;

    skewMatrix[1][0] = in[2]; //<< Az
    skewMatrix[1][1] = 0;
    skewMatrix[1][2] = -in[0]; //<< -Ax
    skewMatrix[1][3] = 0;

    skewMatrix[2][0] = -in[1]; //<< -Ay
    skewMatrix[2][1] = in[0]; //<< Ax
    skewMatrix[2][2] = 0;
    skewMatrix[2][3] = 0;

    skewMatrix[3][0] = 0;
    skewMatrix[3][1] = 0;
    skewMatrix[3][2] = 0;
    skewMatrix[3][3] = 1.0f;

    return skewMatrix;
}

inline
Matrix4D Matrix4D::InertiaTensorCube(Vector4D &extends, float mass)
{
    Matrix4D inertiaTensor;
    float div = 1.0f/12.0f;

    inertiaTensor[0][0] = div*mass*(extends[1]*extends[1] + extends[2]*extends[2]);
    inertiaTensor[1][1] = div*mass*(extends[0]*extends[0] + extends[2]*extends[2]);
    inertiaTensor[2][2] = div*mass*(extends[0]*extends[0] + extends[1]*extends[1]);

    return  inertiaTensor;
}


inline
Matrix4D Matrix4D::InertiaTensorCylinder(float mass, float radius, float height)
{
    Matrix4D inertiaTensor;
    float div = 1.0f/12.0f;

    inertiaTensor[0][0] = div*mass*(height*height) + 0.25f*mass*radius*radius;
    inertiaTensor[1][1] = div*mass*(height*height) + 0.25f*mass*radius*radius;
    inertiaTensor[2][2] = 0.5f*mass*radius*radius;

    return  inertiaTensor;
}

inline
Matrix4D Matrix4D::TranslationMatrix(const Vector4D& other)
{
	Matrix4D new_matrix;
	new_matrix.matrix[0][0] = 0;
	new_matrix.matrix[0][1] = 0;
	new_matrix.matrix[0][2] = 0;
	new_matrix.matrix[0][3] = other.Get(0);

	new_matrix.matrix[1][0] = 0;
	new_matrix.matrix[1][1] = 0;
	new_matrix.matrix[1][2] = 0;
	new_matrix.matrix[1][3] = other.Get(1);

	new_matrix.matrix[2][0] = 0;
	new_matrix.matrix[2][1] = 0;
	new_matrix.matrix[2][2] = 0;
	new_matrix.matrix[2][3] = other.Get(2);

	new_matrix.matrix[3][0] = 0;
	new_matrix.matrix[3][1] = 0;
	new_matrix.matrix[3][2] = 0;
	new_matrix.matrix[3][3] = 0;

	return new_matrix;
}

inline
Matrix4D& Matrix4D::operator+=(const Vector4D& other)
{
	this->matrix[0][3] += other.coordinates[0];
	this->matrix[1][3] += other.coordinates[1];
	this->matrix[2][3] += other.coordinates[2];
	return *this;
}

inline
Matrix4D Matrix4D::operator+(const Matrix4D &other)
{
    Matrix4D newMatrix;

    for(int r = 0; r < 4; r++)
    {
        for(int k = 0; k < 4; k++)
        {
            newMatrix[r][k] = this->matrix[r][k] + other.matrix[r][k];
        }
    }
    newMatrix[3][3] = 1.0f;
    return newMatrix;
}

inline
Matrix4D Matrix4D::operator*(const Matrix4D& other)
{
	Matrix4D new_object;
	int r, k, i;
	float temp = 0;
	for (r = 0; r<4; r++)
	{
		for (k = 0; k<4; k++)
		{
			for (i = 0; i<4; i++)
			{
				temp += this->matrix[k][i] * other.matrix[i][r];
			}
			new_object.matrix[k][r] = temp;
			temp = 0;
		}
	}
	return new_object;
}

inline
Vector4D Matrix4D::operator*(const Vector4D& other)
{
	Vector4D new_vector;
	int r, k;
	float temp = 0;
	for (r = 0; r<4; r++)
	{
		for (k = 0; k<4; k++)
		{
			temp += matrix[r][k] * other.coordinates[k];
		}
		new_vector.coordinates[r] = temp;
		temp = 0;
	}
	return new_vector;
}

inline
Matrix4D Matrix4D::operator*(float val)
{
    Matrix4D new_object;
    int r, k, i;
    float temp = 0;
    for (r = 0; r<4; r++)
    {
        for (k = 0; k<4; k++)
        {
            new_object.matrix[r][k] = this->matrix[r][k]*val;
        }
    }
    return new_object;
}

inline
Matrix4D& Matrix4D::operator=(const Matrix4D& other)
{
	int r, k;
	for (r = 0; r<4; r++)
	{
		for (k = 0; k<4; k++)
			this->matrix[r][k] = other.matrix[r][k];
	}
	return *this;
}

inline
float* Matrix4D::operator[](int val)
{
	return matrix[val];
}

inline
Vector4D Matrix4D::Multiply(Vector4D &other)
{
	Vector4D new_vector;
	int r, k;
	float temp = 0;
	for (r = 0; r<3; r++)
	{
		for (k = 0; k<3; k++)
		{
			temp += matrix[r][k] * other.coordinates[k];
		}
		new_vector.coordinates[r] = temp;
		temp = 0;
	}
	return new_vector;
}

#endif // !VM_MATHLIB