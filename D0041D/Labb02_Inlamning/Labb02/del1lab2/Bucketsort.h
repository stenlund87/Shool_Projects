#pragma once
#include "randtime.h"
/*!Headerfil till bucketsort för arrayer*/
class Bucketsort: public randtime
{
public:
	Bucketsort(int);						///<Konstruktor för Bucketsort
	//~Bucketsort(void);
	std::string name();						///<Metod för att returnera namnet på Bucketsort
	void min_sort(int* arr, int size);		///<Sortertingsfunktionen
};

