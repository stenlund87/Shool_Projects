#pragma once
#include "Vector_Rand.h"
/*!Headerfil till Vector_Insertion f�r vektorer*/
class Vector_Insertion: public Vector_Rand
{
public:
	Vector_Insertion(int);								///< konstruktor f�r Vector_Insertion
	//~Insertionsort(void);
	std::string name();									///< funktion som returnerar namn p� klassen
	void min_sort(std::vector<int>* vec, int size);		///<sorteringsfunktion
	
};

