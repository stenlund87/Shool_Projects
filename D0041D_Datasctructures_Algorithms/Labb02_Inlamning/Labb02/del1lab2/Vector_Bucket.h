#pragma once
#include "Vector_Rand.h"
/*!Headerfil till Vector_Bucket f�r vektorer*/
class Vector_Bucket: public Vector_Rand
{
public:
	Vector_Bucket(int);			///< konstruktor f�r VEctor_Bucket
	//~Vector_Bucket(void);
	std::string name();			///<funktion f�r att f� namn som an�vnds till skriviningen
	void min_sort(std::vector<int>* vec, int size);		///<sorteringsfunktion
};

