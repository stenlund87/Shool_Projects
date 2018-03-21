#include "Vector_Insertion.h"
#include <ctime>


/** konstruktor f�r Vector_Insertion*/
Vector_Insertion::Vector_Insertion(int size)
{
	std::vector<int>*temp = new std::vector<int>(size,0);
	vec = temp;
	vec_size = size;
	run_time=0;
}

/** funktion f�r att returnera namn p� sorteringsfunktion/klass*/
std::string Vector_Insertion::name()
{
	return "Vector_Insertion";
}

//Insertionsort::~Insertionsort(void)
//{
//}

/** sorteringsmetod f�r insertionsort med vektorer som input */
void Vector_Insertion::min_sort(std::vector<int>* vec, int size)
{
	for (int b=0; b<size; b++)
	{
		int min_index = b;
		for (int v=b; v<size; v++)
		{
			if(vec->at(min_index) > vec->at(v))
			{
				min_index = v;
			}
		}
		int holder = vec->at(b);			///<H�rifr�n och ner = swap
		vec->at(b) = vec->at(min_index);
		vec->at(min_index) = holder;
	}
}
