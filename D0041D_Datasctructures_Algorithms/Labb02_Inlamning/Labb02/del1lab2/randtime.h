#pragma once
#include <string>
#include <random>
#include <functional>
/*!Headerfil till randtime f�r arrayer*/
class randtime
{
public:
	randtime(const int &size); ///<konstruktor 
	//~randtime(void);
	randtime();
	enum sorttype{unsorted, sorted, inverted};	///<hur numren ligger i arrayen
	void runtime();								///<funktionen som kommer ta tid ochn skriva till textfil 
	void write(sorttype h);						///<funktion f�r att skriva till fil
	int randomnumber();							///<funktion f�r att f� randomnummer
	//virtual void max_sort(int *arr, int size);
	virtual void min_sort(int *arr, int size);	///<sorteringsfunktion
	virtual std::string name();					///<funktion f�r att f� namn som an�vnds till skriviningen
	void print_array();							///<funktion som skriver ut array
	void fillsort();							///<funktion som fyller array s� den blir sorterad
	void fillrandom();							///<funktion som fyller array med random nummer upp till storlekan av arrayen 
	void fillinvert();							///< fyller array men inverterat
	void delarr();								///<funktion som tar bort array som pekas p�
	
	sorttype type;

	int* arr;									///< int pekare f�r arrays
	int size_array;								///< variable f�r storleken av array
	std::mt19937 mt;							///< random nummergenerator

protected:

	double run_time;							///< variabel f�r tid som sorteringen tar

};

