#pragma once
#include "randtime.h"

/*!Headerfil till insertionsort f�r arrayer*/
class quicksort: public randtime
{
public:
	quicksort(int size);
	//~quicksort();
	std::string name();
	void min_sort(int* arr, int left, int size); ///<sorterings metoden som kallas i min_sort f�r quicksort
	void min_sort(int* arr, int size); ///< sorteringsfunktionen som vi kallar i funktionen runtime som ligger i randtime klassen 
};

