#pragma once
#include "randtime.h"
/*!Headerfil till bucketsort f�r arrayer*/
class Bucketsort: public randtime
{
public:
	Bucketsort(int);						///<Konstruktor f�r Bucketsort
	//~Bucketsort(void);
	std::string name();						///<Metod f�r att returnera namnet p� Bucketsort
	void min_sort(int* arr, int size);		///<Sortertingsfunktionen
};

