#include "quicksort.h"

/** konstruktor f�r quicksort*/
quicksort::quicksort(int size):randtime(size){}
/** funktion f�r att returnera namn av klass/sorteringmetod*/
std::string quicksort::name()
{
	return "Quicksort";
}

//quicksort::~quicksort()
//{
//	delete[] arr;
//}

/** sorteringsmetod f�r quicksorten*/
void quicksort::min_sort(int* arr, int left, int right)
{
	int pivot = arr[(left + right)/2]; ///< R�knar ut en "medianv�rde" som anv�nds f�r att j�mf�ra alla tal i arrayen
	int l = left;
	int r = right;
	while(l <= r)
	{
		while (arr[l] < pivot)		///< Medans v�rdet som v�nstra iteratorn "pekar" p� �r mindre �n pivot s� flyttar vi iteratorn ett steg �t h�ger
		{
			l++;		
		}

		while(arr[r] > pivot)		///< Medans v�rdet som h�gra iteratorn "pekar" p� �r st�rre s� flyttar vi iteratorn ett steg �t v�nster
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

/** funktion som kallas fr�n runtime f�r att sortera*/
void quicksort::min_sort(int* arr, int size)
{
	min_sort(arr,0,size-1);
}

