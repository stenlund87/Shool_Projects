#pragma once
#include "randtime.h"
/*!Headerfil till heapsorten för arrayer*/
class Heapsort: public randtime
{
public:
	Heapsort(int);
	//~Heapsort(void);
	std::string name();
	void min_sort(int* , int); ///< sorteringsfunktionen som vi kallar i funktionen runtime som ligger i randtime klassen 
	void swaps(int *arr, int , int);  ///< heapify
	void heapsort(int *arr, int );		
	void build_heap(int *arr, int );
};

