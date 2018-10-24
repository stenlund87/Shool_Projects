#include "quicksort.h"

/** konstruktor för quicksort*/
quicksort::quicksort(int size):randtime(size){}
/** funktion för att returnera namn av klass/sorteringmetod*/
std::string quicksort::name()
{
	return "Quicksort";
}

//quicksort::~quicksort()
//{
//	delete[] arr;
//}

/** sorteringsmetod för quicksorten*/
void quicksort::min_sort(int* arr, int left, int right)
{
	int pivot = arr[(left + right)/2]; ///< Räknar ut en "medianvärde" som används för att jämföra alla tal i arrayen
	int l = left;
	int r = right;
	while(l <= r)
	{
		while (arr[l] < pivot)		///< Medans värdet som vänstra iteratorn "pekar" på är mindre än pivot så flyttar vi iteratorn ett steg åt höger
		{
			l++;		
		}

		while(arr[r] > pivot)		///< Medans värdet som högra iteratorn "pekar" på är större så flyttar vi iteratorn ett steg åt vänster
		{
			r--;
		}

		if(l <= r)
		{
			int temp = arr[l];
			arr[l] = arr[r];
			arr[r] = temp;
			l++;
			r--;
		}
	}

	if(left < r)
	{
		min_sort(arr, left, r);
	}
	if(l < right)
	{
		min_sort(arr, l, right);
	}
}

/** funktion som kallas från runtime för att sortera*/
void quicksort::min_sort(int* arr, int size)
{
	min_sort(arr,0,size-1);
}

