#pragma once
#include "Vector_Rand.h"

/*!Headerfil till Vector_Quick f�r vektorer*/
class Vector_Quick: public Vector_Rand
{
public:
	Vector_Quick(int size);										///<konstruktor f�r Vector_Quick
	//~quicksort();
	std::string name();											///<funktion som returnerar namn p� klassen
	void min_sort(std::vector<int>* vec, int left, int size);  ///<sorterings metoden som kallas i min_sort f�r Vector_Quicksort
	void min_sort(std::vector<int>* vec, int size);				///< sorteringsfunktionen som vi kallar i funktionen runtime som ligger i randtime klassen 
};

