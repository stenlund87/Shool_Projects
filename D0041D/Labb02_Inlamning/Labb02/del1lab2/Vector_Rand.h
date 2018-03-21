#pragma once
#include <vector>
#include <string>
#include <random>
#include <functional>
/*!Headerfil till randtime för vektorer*/
class Vector_Rand
{
public:
	Vector_Rand(const int &size);								////<konstruktor för Vector_rand 
	Vector_Rand();
	//~randtime(void);
	enum sorttype{unsorted, sorted, inverted};					///<hur numren ligger i vektorn
	void runtime();												///<funktionen som kommer ta tid ochn skriva till textfil 
	void write(sorttype h);										///< funktoinen som skriver ut till textfil
	int randomnumber();											///< funktion som generar ett random nummer från 0 till storleken av vektorn
	//virtual void max_sort(int *arr, int size);
	virtual void min_sort(std::vector<int>* vec, int size);		///< sorteringsfunktionen till vektorna
	virtual std::string name();									///< funktion som används i underklasserna för att få namnet på klassen
	void print_vector();										///< gör cout på elementen i vektorn
	void fillsort();											///< fyller vektorn med element i sorterad ordning
	void fillrandom();											///< fyller vektorn med random element med max storlek av vektorn  storlek
	void fillinvert();											///< fyller vektorn med element i inverterad ordning

	void vecdel();												
	sorttype type;												///< variabel till enumeratorn

	std::vector<int>* vec;										///< vektor pekare
	int vec_size;												///< variabel för storleken av vekotrn
	
	std::mt19937 mt;											///< random generatorn

protected:

	double run_time;											///< variable som är tänkt hålla den tiden sorteringen tar

};

