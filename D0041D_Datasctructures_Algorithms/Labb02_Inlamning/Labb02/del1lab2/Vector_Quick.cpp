#include "Vector_Quick.h"

/** konstruktor för Vector_Quick*/
Vector_Quick::Vector_Quick(int size):Vector_Rand(size){}

std::string Vector_Quick::name()
{
	return "Vector_Quick";
}

//Vector_Quick::~Vector_Quick()
//{
//	delete[] vec;
//}

/** sorteringmetoden för quicksort med vektorer*/
void Vector_Quick::min_sort(std::vector<int>* vec, int left, int right)
{
	int pivot = vec->at((left + right)/2);
	int l = left;
	int r = right;
	while(l <= r)
	{
		while (vec->at(l) < pivot)
		{
			l++;		
		}
		while(vec->at(r) > pivot)
		{
			r--;
		}
		if(l <= r)						///< Swap
		{
			int temp = vec->at(l);
			vec->at(l) = vec->at(r);
			vec->at(r) = temp;
			l++;
			r--;
		}
	}

	if(left < r)
	{
		min_sort(vec, left, r);
	}
	if(l < right)
	{
		min_sort(vec, l, right);
	}
}

/** funktionen som kallas från runtime*/
void Vector_Quick::min_sort(std::vector<int>* vec, int size)
{
	min_sort(vec,0,size-1);
}

