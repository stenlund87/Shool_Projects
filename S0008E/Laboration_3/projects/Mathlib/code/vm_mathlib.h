#ifndef VM_MATHLIB
#define VM_MATHLIB

#include <array>
#include <exception>
#include <iostream>
#include <math.h>
#include <algorithm>


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
	float QuaternionLength();
	void NormalizeQuaternion();
	float QuaternionDot(const Vector4D &other);
	Vector4D SlerpQuaternion(Vector4D &lh, Vector4D &rh, float dt);
	Vector4D Lerp(const Vector4D &lh,const Vector4D &rh, float dt);

	//Overloaded operators
	Vector4D operator+(Vector4D& other); //overload on + and creates a new object of Vector4D
	Vector4D operator+(float number); //Overload on + and changes the values inside the Vector4D
	Vector4D operator-(const Vector4D& other); //Overload on - and creates a new object of Vector4D
	Vector4D& operator=(const Vector4D& other); //Overloadon = and creates a new object of Vector4D
	float operator*(const Vector4D& other); //Overload on * for DotProduct
	Vector4D& operator*(float number); //Overload for scaling
	bool operator==(const Vector4D& other);
	bool operator!=(const Vector4D& other);
	float* operator[](int index); //Overload for getting the value in the array, you may change the value

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
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;
}

inline
Vector4D Vector4D::CrossProduct(const Vector4D& other)
{
	Vector4D new_object;
	new_object.coordinates[0] = this->coordinates[1] * other.coordinates[2] - this->coordinates[2] * other.coordinates[1];
	new_object.coordinates[1] = this->coordinates[2] + other.coordinates[0] - this->coordinates[0] * other.coordinates[2];
	new_object.coordinates[2] = this->coordinates[0] + other.coordinates[1] - this->coordinates[1] * other.coordinates[0];
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

inline float Vector4D::QuaternionLength()
{
	float length;
	length = coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1] + coordinates[2] * coordinates[2] + coordinates[3]*coordinates[3];
	length = sqrtf(length);
	return length;
}

inline Vector4D Vector4D::Normalize()
{
    Vector4D norm;

    if(Length() != 0)
	{
		float length, u, v, w;
		length = 1.0f / Length();
		v = coordinates[0] * length;
		u = coordinates[1] * length;
		w = coordinates[2] * length;

		norm.coordinates[0] = v;
        norm.coordinates[1] = u;
        norm.coordinates[2] = w;
	}
    return norm;
}

inline void Vector4D::NormalizeQuaternion()
{
	if(Length() != 0)
	{
		float length;
		length = 1.0f / QuaternionLength();
		coordinates[0] = coordinates[0] * length;
		coordinates[1] = coordinates[1] * length;
		coordinates[2] = coordinates[2] * length;
		coordinates[3] = coordinates[3] * length;
	}
}

inline float Vector4D::QuaternionDot(const Vector4D &other)
{
	float product;
	product = this->coordinates[0] * other.coordinates[0] + this->coordinates[1] * other.coordinates[1] + this->coordinates[2] * other.coordinates[2] + this->coordinates[3] * other.coordinates[3];
	return product;
}

inline Vector4D Vector4D::SlerpQuaternion(Vector4D &lh, Vector4D &rh, float dt)
{
	lh.NormalizeQuaternion();
	rh.NormalizeQuaternion();

	float x;
	float y;
	float z;
	float w;

	double dot = lh.QuaternionDot(rh);
	const double dotThreshold = 0.9999999999999995;

	if(fabs(dot) > dotThreshold)
	{
		 x = lh.coordinates[0] + dt*(rh.coordinates[0]-lh.coordinates[0]);
		 y = lh.coordinates[1] + dt*(rh.coordinates[1]-lh.coordinates[1]);
		 z = lh.coordinates[2] + dt*(rh.coordinates[2]-lh.coordinates[2]);
		 w = lh.coordinates[3] + dt*(rh.coordinates[3]-lh.coordinates[3]);
		Vector4D result(x,y,z,w);

		result.NormalizeQuaternion();

		return result;
	}

	if(dot < 0.0f)
	{
		rh.coordinates[0] = -rh.coordinates[0];
		rh.coordinates[1] = -rh.coordinates[1];
		rh.coordinates[2] = -rh.coordinates[2];
		rh.coordinates[3] = -rh.coordinates[3];
		dot = -dot;
	}
	if(dot > 1)
	{
		dot = 1;
	}
	else if( dot < -1)
	{
		dot = -1;
	}
	float angle = acos(dot);
	float theta = angle * dt;

	x = rh.coordinates[0] - lh.coordinates[0]*dot;
	y = rh.coordinates[1] - lh.coordinates[1]*dot;
	z = rh.coordinates[2] - lh.coordinates[2]*dot;
	w = rh.coordinates[3] - lh.coordinates[3]*dot;

	Vector4D v3(x,y,z,w);
	v3.NormalizeQuaternion();
	
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);

	float newX = lh.coordinates[0]*cosTheta + v3.coordinates[0]*sinTheta;
	float newY = lh.coordinates[1]*cosTheta + v3.coordinates[1]*sinTheta;
	float newZ = lh.coordinates[2]*cosTheta + v3.coordinates[2]*sinTheta;
	float newW = lh.coordinates[3]*cosTheta + v3.coordinates[3]*sinTheta;

	Vector4D test(newX, newY, newZ, newW);

	return test;
}


inline Vector4D Vector4D::Lerp(const Vector4D &lh,const Vector4D &rh, float dt)
{
	float x1, y1,z1 ,w1, x2, y2, z2, w2;
	x1 = lh.coordinates[0];
	y1 = lh.coordinates[1];
	z1 = lh.coordinates[2];
	w1 = lh.coordinates[3];

	x2 = rh.coordinates[0];
	y2 = rh.coordinates[1];
	z2 = rh.coordinates[2];
	w2 = rh.coordinates[3];

	float x = (1.0f-dt) * x1 + dt * x2;
	float y = (1.0f-dt) * y1 + dt * y2;
	float z = (1.0f-dt) * z1 + dt * z2;

	Vector4D result(x,y,z,1);
//	result.Normalizing();
	return result;
}

//Overloadar operatorn + s� att ett nytt objekt av samma klass skapas med de sammanslagna v�rderna
inline Vector4D Vector4D::operator+(Vector4D& other)
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
	this->coordinates[0] = this->coordinates[0] + number;
	this->coordinates[1] = this->coordinates[1] + number;
	this->coordinates[2] = this->coordinates[2] + number;
	return *this;
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

inline Vector4D& Vector4D::operator*(float number)
{
	this->coordinates[0] = this->coordinates[0] * number;
	this->coordinates[1] = this->coordinates[1] * number;
	this->coordinates[2] = this->coordinates[2] * number;
	this->coordinates[3] = this->coordinates[3] * number;
	return *this;
}

inline bool Vector4D::operator==(const Vector4D& other)
{
	return (this->coordinates[0] == other.coordinates[0] && this->coordinates[1] == other.coordinates[1] && this->coordinates[2] == other.coordinates[2] != other.coordinates[3]);
}

inline bool Vector4D::operator!=(const Vector4D& other)
{
	return (this->coordinates[0] != other.coordinates[0] || this->coordinates[1] != other.coordinates[1] || this->coordinates[2] != other.coordinates[2] != other.coordinates[3]);
}

inline float* Vector4D::operator[](int index)
{
	return &coordinates[index];
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
	 * Method that transforms a matrix to a representation of a Quaternion
	 * @param other
	 */
	void Quaternion(const Vector4D& other);

	/**
	 * Create a scalar matrix
	 * @param other, vector that represents the scale
	 * @return a new Matrix with scale
	 */
	static Matrix4D Scale(const Vector4D& other);

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
     * Method that returns the position column as a Vector4D from a transformation matrix
     * @return
     */
    Vector4D GetPosition();
	Matrix4D MultiplyFloat(float val);

    float* ConvertMatrix();

	/**
	*Adds the value of the vector to the last column of the matrix
	*/
	Matrix4D& operator+=(const Vector4D& other);

	/**
	*Overloaded operator for multiplication for two matrix
	*@return, a new object of type Matrix4D
	*/
	Matrix4D operator*(const Matrix4D& other);

	/**
	*Overloaded operator for multiplication between matrix and vector
	*@return a new object of type Vector4D
	*/
	Vector4D operator*(const Vector4D& other);


	/**
	*Overloaded operator for copying a matrix;
	*/
	Matrix4D& operator=(const Matrix4D& other);

	Matrix4D operator+(const Matrix4D& other);

	/**
	*Overloaded operator for getting the value in the matrix;
	*/
	float* operator[](int val);
	Matrix4D operator*(float val);

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
void Matrix4D::Quaternion(const Vector4D &other)
{
    float x = other.coordinates[0];
    float y = other.coordinates[1];
    float z = other.coordinates[2];
    float w = other.coordinates[3];

	this->matrix[0][0] = 1 - (2 * (y * y)) - (2 * (z*z)); //<< 1 - 2y*y - 2z*z
	this->matrix[0][1] = 2 * (x*y) + 2 * (w*z); //<< 2x*y + 2*w*z
	this->matrix[0][2] = 2 * (x*z) - 2 * (w*y); //<< 2*x*z - 2*w*y

	this->matrix[1][0] = 2 * (x*y) - 2 * (w*z); //<< 2*x*y - 2*w*z
	this->matrix[1][1] = 1 - 2 * (x*x) - 2 * (z*z); //<< 1 - 2*x*x - 2*z*z
	this->matrix[1][2] = 2 * (y*z) + 2 * (w*x); //<< 2*y*z + 2*w*x

	this->matrix[2][0] = 2 * (x*z) + 2 * (w*y); //<< 2*x*z + 2*w*y
	this->matrix[2][1] = 2 * (y*z) - 2 * (w*x); //<< 2*y*z - 2*w*x
	this->matrix[2][2] = 1 - 2 * (x*x) - 2 * (y*y); //<< 1 - 2*x*x - 2*y*y

}

inline
Matrix4D Matrix4D::Scale(const Vector4D &other)
{
	Matrix4D scaleMatrix;
	scaleMatrix[0][0] = other.coordinates[0];
	scaleMatrix[1][1] = other.coordinates[1];
	scaleMatrix[2][2] = other.coordinates[2];
	return scaleMatrix;
}

inline
Matrix4D Matrix4D::Transpose()
{
	Matrix4D new_object;
	int r, k;
	for (r = 0; r<4; r++)
		for (k = 0; k<4; k++)
			new_object.matrix[k][r] = this->matrix[r][k];
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

			arr[4] = matrix[1][0] * matrix[2][3] * matrix[3][2] + matrix[1][2] * matrix[2][0] * matrix[3][3] + matrix[1][3] * matrix[2][2] * matrix[3][0] - matrix[1][0] * matrix[2][2] * matrix[3][3] - matrix[1][2] * matrix[2][3] * matrix[3][0] - matrix[1][3] * matrix[2][0] * matrix[3][2];
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
		std::cout << "There exist no inverse for the matrix";
	}
}

inline
Vector4D Matrix4D::GetPosition()
{
    return Vector4D(matrix[0][3], matrix[1][3], matrix[2][3]);
}

inline
Matrix4D Matrix4D::TranslationMatrix(const Vector4D& other)
{
	Matrix4D new_matrix;
	new_matrix.matrix[0][0] = 1;
	new_matrix.matrix[0][1] = 0;
	new_matrix.matrix[0][2] = 0;
	new_matrix.matrix[0][3] = other.Get(0);

	new_matrix.matrix[1][0] = 0;
	new_matrix.matrix[1][1] = 1;
	new_matrix.matrix[1][2] = 0;
	new_matrix.matrix[1][3] = other.Get(1);

	new_matrix.matrix[2][0] = 0;
	new_matrix.matrix[2][1] = 0;
	new_matrix.matrix[2][2] = 1;
	new_matrix.matrix[2][3] = other.Get(2);

	new_matrix.matrix[3][0] = 0;
	new_matrix.matrix[3][1] = 0;
	new_matrix.matrix[3][2] = 0;
	new_matrix.matrix[3][3] = 1;

	return new_matrix;
}

inline
float* Matrix4D::ConvertMatrix()
{
    float arr[16];
    int r = 0;
    for(int i = 0; i<16; i++)
    {
        arr[i] = matrix[r][i];
        if(i == 3 || i == 6 || i == 9)
        {
            matrix[r][i];
            r++;
        }
    }
	arr[15] = 1;
    return arr;
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
Matrix4D Matrix4D::operator*(float val)
{
	Matrix4D newMatrix;
	for (int r = 0; r<4; r++)
	{
		for (int k = 0; k<4; k++)
			newMatrix.matrix[r][k] = this->matrix[r][k] * val;
	}
	return newMatrix;
}

inline
Matrix4D Matrix4D::operator+(const Matrix4D &other)
{
	Matrix4D nm;
	for(int r = 0; r<4; r++)
	{
		for(int k = 0; k < 4; k++)
		{
			nm.matrix[r][k] = this->matrix[r][k] + other.matrix[r][k];
		}
	}
	return nm;
}


#endif // !VM_MATHLIB
