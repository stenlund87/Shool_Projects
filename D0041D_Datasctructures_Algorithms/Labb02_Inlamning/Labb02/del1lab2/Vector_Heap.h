#pragma once
#include "Vector_Rand.h"
/*!Headerfil till Vector_Heap f�r vektorer*/
class Vector_Heap: public Vector_Rand
{
public:
	Vector_Heap(int);								///<konstruktor f�r Vector_Heap
	//~Heapsort(void);
	std::string name();								///< funktion som returnerar namn p� klassen 
	void min_sort(std::vector<int>* vec , int);		///<sorteringsfunktion
	void swaps(std::vector<int>* vec, int , int);	///< heapify
	void heapsort(std::vector<int>* vec, int );		
	void build_heap(std::vector<int>* vec, int );	///< funktion som bygger upp heap
};

