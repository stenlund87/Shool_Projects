#pragma once
#include "randtime.h"
/*!Headerfil till insertionsort f�r arrayer*/
class Insertionsort: public randtime
{
public:
	Insertionsort(int);					///<Konstruktor f�r Insertionsort
	std::string name();
	void min_sort(int* arr, int size); ///< sorteringsfunktionen som vi kallar i funktionen runtime som ligger i randtime klassen 
	
};

