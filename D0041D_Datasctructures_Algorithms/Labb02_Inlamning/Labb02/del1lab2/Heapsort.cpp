#include "Heapsort.h"
#include <iostream>

/**konstruktor för bucketsort*/
Heapsort::Heapsort(int size):randtime(size){}


//Heapsort::~Heapsort(void)
//{
//}

/**funktionen som kallas när vi ska sortera i runtime*/
void Heapsort::min_sort(int *arr, int size)					
{
	build_heap(arr, size);
	heapsort(arr,size);	
}

/**funktion för att returnera namn på klass/sorteringmetod*/
std::string Heapsort::name()								
{
	return "Heapsort";
}

/**heapify*/
void Heapsort::swaps(int *arr, int i, int size)				
{
    int j, temp;
    temp = arr[i];
    j = 2*i;

    while (j < size)
    {
        if (j < size && arr[j+1] > arr[j])
            j = j+1;
        if (temp >= arr[j])
            break;
        else if (temp < arr[j])
        {
            arr[j/2] = arr[j];
            j = 2*j;
        }
    }
    arr[j/2] = temp;
    return;
}

/**själva sorteringsfunktionen*/
void Heapsort::heapsort(int *arr, int size)					
{
    int temp;
	
    for (int i = size-1; i >= 1; i--)	///<Swappar
    {
        temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        swaps(arr, 0, i - 1);
    }
}

/**konstruktor för bucketsort*/
void Heapsort::build_heap(int *arr, int n)					///< funktion för att bygga heap i början
{
    for(int i = (n-1)/2; i >= 0; i--)
    {
        swaps(arr, i, n);
    }
}