#include "Vector_Heap.h"
#include <iostream>
/** konstruktor för Vector_Heap*/
Vector_Heap::Vector_Heap(int size)
{
	std::vector<int>*temp = new std::vector<int>(size,0);
	vec = temp;
	vec_size = size;
	run_time=0;
}

//Vector_Heap::~Vector_Heap(void)
//{
//}

/** sorteringsfunktionen som kallas från runtime*/
void Vector_Heap::min_sort(std::vector<int>* vec, int size)
{
	build_heap(vec, size);
	heapsort(vec,size);
}

/** funktion som returnerar namn på soreteringmetod/klass*/
std::string Vector_Heap::name()
{
	return "Vector_Heap";
}

/** heapify funktion*/
void Vector_Heap::swaps(std::vector<int>* vec, int i, int size)
{
    int j, temp;
    temp = vec->at(i);
    j = 2*i;

    while (j < size)
    {
		if ( j== size-1 && size >1) 
			goto ref;
		
        if (j < size && vec->at(j+1) > vec->at(j))
            j = j+1;
			
		ref:
        if (temp >= vec->at(j))
            break;
        else if (temp < vec->at(j))
        {
            vec->at(j/2) = vec->at(j);
            j = 2*j;
        }
    }
    vec->at(j/2) = temp;
}

/** själva sorteringsunktionen */
void Vector_Heap::heapsort(std::vector<int>* vec, int size)
{
    int temp;
    for (int i = size-1; i >= 1; i--)
    {
		std::swap(vec->at(0),vec->at(i));
        swaps(vec, 0, i - 1);
    }
}

/** bygger en heap*/
void Vector_Heap::build_heap(std::vector<int>* vec, int n)
{
    for(int i = (n-1)/2; i >= 0; i--)
    {
        swaps(vec, i, n);
    }
}