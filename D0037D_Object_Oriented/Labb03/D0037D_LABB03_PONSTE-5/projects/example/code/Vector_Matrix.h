#ifndef Vector_Matrix.h
#define Vector_Matrix

#include <array>




class Vector2D
{
	public:	
		friend class Matrix2D;


		Vector2D(float x,float y); //konstruktor när man vill skicka med koordinater
		Vector2D(); //konstruktor när man inte vill skicka in koordinater direkt
		Vector2D(const Vector2D& other); //konstruktor för kopiering

		void Addition(const Vector2D& other);
		void Substract(const Vector2D& other);
		float Get(int indx);
		void Set(float x,float y);
		float DotProduct(const Vector2D& other);
		float Length();
		void Normalizing();

		Vector2D operator+(Vector2D& other); //overload på + och skapar ett nytt object av klassen
		Vector2D operator-(const Vector2D& other); //overload på - och skapar ett nytt object av klassen
		Vector2D operator=(const Vector2D& other); //overload på = och skapar ett nytt object av klassen
		Vector2D operator*(const Vector2D& other); //overload på * och skapar ett nytt object av klassen
		bool operator==(const Vector2D& other);
		bool operator!=(const Vector2D& other);

		
		float coordinates[2];



		

};


class Matrix2D
{
	public:
		friend class Vector2D;
		//constructor of an identity matrix
		Matrix2D();

		//constructor for copying an object
		Matrix2D(const Matrix2D& original); 

		//constructor when the user sends in values to the matrix
		Matrix2D(float a, float b, float c, float d); 

		/**
		 *Returns the value from the row and column
		 *@param row, index (0-1)
		 *@param col, index (0-1)
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


		//Return a new object with a transpose matrix of the matrix that calls the method
		Matrix2D Transpose();

	 /**
	  * Return  a matrix for rotating a vector a given number of degrees.
	  * @param degree Degrees in radians.
	  * @return Rotation matrix.
	 */
		static Matrix2D Rotation(float degree);

		/**
		 *Return a new object of the class Vector2D.
		 *@param an object of the class Vector2D.
		 *@return Transformation vektor
		*/
		Vector2D Tranformation(const Vector2D& other);

		Matrix2D operator*(const Matrix2D& other);
		Matrix2D& operator=(const Matrix2D& other);	
		Matrix2D Matrix2D::operator*(const Vector2D& other);
	
		float matrix[2][2];

};

#endif