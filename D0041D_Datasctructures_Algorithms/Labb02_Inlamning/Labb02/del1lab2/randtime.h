#pragma once
#include <string>
#include <random>
#include <functional>
/*!Headerfil till randtime för arrayer*/
class randtime
{
public:
	randtime(const int &size); ///<konstruktor 
	//~randtime(void);
	randtime();
	enum sorttype{unsorted, sorted, inverted};	///<hur numren ligger i arrayen
	void runtime();								///<funktionen som kommer ta tid ochn skriva till textfil 
	void write(sorttype h);						///<funktion för att skriva till fil
	int randomnumber();							///<funktion för att få randomnummer
	//virtual void max_sort(int *arr, int size);
	virtual void min_sort(int *arr, int size);	///<sorteringsfunktion
	virtual std::string name();					///<funktion för att få namn som anävnds till skriviningen
	void print_array();							///<funktion som skriver ut array
	void fillsort();							///<funktion som fyller array så den blir sorterad
	void fillrandom();							///<funktion som fyller array med random nummer upp till storlekan av arrayen 
	void fillinvert();							///< fyller array men inverterat
	void delarr();								///<funktion som tar bort array som pekas på
	
	sorttype type;

	int* arr;									///< int pekare för arrays
	int size_array;								///< variable för storleken av array
	std::mt19937 mt;							///< random nummergenerator

protected:

	double run_time;							///< variabel för tid som sorteringen tar

};

