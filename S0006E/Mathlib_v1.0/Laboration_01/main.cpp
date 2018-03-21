#include "Vector_Matrix_Mathlib.h"
#include <iostream>


int main()
{
	Matrix4D hej(1,2,3,4,5,6,7,8,9);
	//Matrix4D bla = hej.Inverse();
	Vector4D tjo(1,2,3);
	Matrix4D blah = hej.Rotation_Vector(tjo,90);
	Matrix4D ti = hej*blah;

	for (int r = 0; r < 4; r++)
	{
		for (int k = 0; k < 4; k++)
		{
			std::cout << ti[r][k] << std::endl;
		}
	}
	std::cout << tjo[0];
	int x;
	std::cin >> x;
}