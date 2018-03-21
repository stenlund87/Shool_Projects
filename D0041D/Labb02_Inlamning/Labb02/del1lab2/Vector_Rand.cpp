#include "Vector_Rand.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <typeinfo>
#include <random>
#include <functional>

/** konstruktor f�r Vector_Rand*/
Vector_Rand::Vector_Rand( const int &size)
{
	std::vector<int>*temp = new std::vector<int>(size,0);
	vec = temp;
	vec_size = size;
	run_time=0;
}

Vector_Rand::Vector_Rand()
{
}

//Vector_Rand::~Vector_Rand(void)
//{
//	delete[] vec;
//}

/** Returnerar namnet p� klassen */
std::string Vector_Rand::name()
{
	return "Vector_Rand";
}

/**Fyller vektorn med sorterade tal fr�n 0->sizen */
void Vector_Rand::fillsort()
{
	int r=0;
	for (int i=0; i<vec_size; i++)
	{
		vec->at(i)=r;
		r++;
	}
	type=sorted;
}
/**Anropar Vector_Rand's randomnumber f�r att f� ett slumptal fr�n mt19937 och stoppar in det i vektorn */
void Vector_Rand::fillrandom()
{
	int r;
	unsigned beginning = std::chrono::system_clock::now().time_since_epoch().count();  ///< skapar en seed s� att vi f�r slumpm�ssiga tal 
	mt.seed(beginning);																   ///< seedar mt19937

	for (int i=0; i<vec_size; i++)
	{
		r=randomnumber();													
		vec->at(i)=r;
	}
	type=unsorted;
}


/**Fyller vektorn med tal fr�n size->0 */
void Vector_Rand::fillinvert()
{
	int r=vec_size;
	for (int i=0; i<vec_size; i++)
	{
		vec->at(i)=r;
		r--;
	}
	type=inverted;
}

/**Skapar tv� timestamps och r�knar ut hur l�ng tid sorteringen tog och anropar write*/
void Vector_Rand::runtime()
{
	sorttype holder;
	holder= this->type;
	using namespace std::chrono;

	time_point<steady_clock>;
	steady_clock::time_point t0 = steady_clock::now();
	min_sort(vec,this->vec_size);
	steady_clock::time_point t1 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t1 - t0);
	run_time = time_span.count();
	write(holder);
}

/**G�r till slutet av test.txt och skriver ner vilken sorteringsalgoritm som anv�ndes, storleken, tiden det tog att sortera och hur vektorn s�g ut innan k�rning */
void Vector_Rand::write(sorttype h) //Fixa argument f�r om listan �r osorterad/sorterad eller inventerad
{
	std::fstream myfile;
	myfile.open("test.txt",std::ios::app);
	myfile << name() << std::endl;
	myfile << vec_size << std::endl;
	myfile << run_time << " seconds" << std::endl;

	if(h == unsorted) myfile << "random" << std::endl;
	else if(h == sorted) myfile << "Sorted" << std::endl;
	else if (h == inverted) myfile << "Inverted" << std::endl;
	myfile << "-----------------------------------------" << std::endl;

	myfile << "\n";
	myfile.close();
}

/**Returnerar ett slumptal*/
int Vector_Rand::randomnumber()
{	
	std::uniform_int_distribution<int> dist(0,vec_size);
	return dist(mt);
}

/**Virtuel funktion som inte beh�vs i Vector_Rand */
void Vector_Rand::min_sort(std::vector<int>* vec, int size)
{
}

/**Metod som skriver ut hela vektorn */
void Vector_Rand::print_vector()
{
	for (auto i = vec->begin(); i != vec->end(); ++i)
		std::cout << *i << std::endl;
}

/**Av-allokerar minnet som vec pekar p� och s�tter vec till nullptr */
void Vector_Rand::vecdel()
{
	delete vec;
	vec=nullptr;
}
