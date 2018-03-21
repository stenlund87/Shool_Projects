#include "Insertionsort.h"
#include <ctime>


/**konstruktor för insertionsort*/
Insertionsort::Insertionsort(int size)
{
	arr = new int[size];
	size_array = size;
	run_time=0;
	type=unsorted;
}

/** funktion för att returnera namn av klass/sorteringmetod*/
std::string Insertionsort::name()
{
	return "Insertionsort";
}

//Insertionsort::~Insertionsort(void)
//{
//}

/**sorteringsmetoden för insertionsort*/
void Insertionsort::min_sort(int *arr, int size)
{
	for (int b=0; b<size; b++)						
	{
		int min_index = b;
		for (int v=b; v<size; v++)
		{
			if(arr[min_index]> arr[v])
			{
				min_index = v;
			}
		}
		int holder = arr[b];
		arr[b] =arr[min_index];
		arr[min_index] = holder;
	}
}
