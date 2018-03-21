#pragma once
#include "Vector_Rand.h"
/*!Headerfil till Vector_Bucket för vektorer*/
class Vector_Bucket: public Vector_Rand
{
public:
	Vector_Bucket(int);			///< konstruktor för VEctor_Bucket
	//~Vector_Bucket(void);
	std::string name();			///<funktion för att få namn som anävnds till skriviningen
	void min_sort(std::vector<int>* vec, int size);		///<sorteringsfunktion
};

