#pragma once
#include "Vector_Rand.h"
/*!Headerfil till Vector_Insertion för vektorer*/
class Vector_Insertion: public Vector_Rand
{
public:
	Vector_Insertion(int);								///< konstruktor för Vector_Insertion
	//~Insertionsort(void);
	std::string name();									///< funktion som returnerar namn på klassen
	void min_sort(std::vector<int>* vec, int size);		///<sorteringsfunktion
	
};

