#include "randtime.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <typeinfo>
#include <random>
#include <functional>
#include "Insertionsort.h"

/**Konstruktor till randtime f�r arrayer*/
randtime::randtime( const int &size)
{
	arr = new int[size];
	size_array = size;
	run_time=0;
}

/**default konstruktor*/
randtime::randtime(void)
{
}

//randtime::~randtime(void)
//{
//	delete[] arr;
//}

/**default konstruktor*/
std::string randtime::name()
{
	return "Randtime";
}

/**funktion f�r att fylla array med element i sorterad ordning*/
void randtime::fillsort()
{
	int r=0;
	for (int i=0; i<size_array; i++)
	{
		arr[i]=r;
		r++;
	}
	type=sorted;																///< s�tter vilken sorts ordning arrayen har
}

/**funktion f�r att fylla array med randomiserat element*/
void randtime::fillrandom()
{
	int r;
	unsigned beginning = std::chrono::system_clock::now().time_since_epoch().count(); 
	mt.seed(beginning);

	for (int i=0; i<size_array; i++)
	{
		r=randomnumber();
		arr[i]=r;
	}
	type=unsorted;																///< s�tter vilken sorts ordning arrayen har
}

/**funktion f�r att fylla array med element i inverterad ordning*/
void randtime::fillinvert()
{
	int r=size_array;
	for (int i=0; i<size_array; i++)
	{
		arr[i]=r;
		r--;
	}
	type=inverted;																///< s�tter vilken sorts ordning arrayen har
}

/**funktion f�r att ta tid och ssedan skriva in det i textfil*/
void randtime::runtime()
{
	const std::type_info& object_type = typeid(this);
	sorttype holder;
	holder= this->type;
	using namespace std::chrono;

	time_point<steady_clock>;
	steady_clock::time_point t0 = steady_clock::now();							///<Skapar f�rsta timestampen
	min_sort(arr,this->size_array);
	steady_clock::time_point t1 = steady_clock::now();							///<Skapar andra timestampen
	duration<double> time_span = duration_cast<duration<double>>(t1 - t0);		///<R�knar ut skillnaden
	run_time = time_span.count();
	write(holder);
}

/**funktionen som anv�nds till att skriva in i textfilen*/
void randtime::write(sorttype h) //Fixa argument f�r om listan �r osorterad/sorterad eller inventerad
{
	std::fstream myfile;
	myfile.open("test.txt",std::ios::app);
	myfile << name() << std::endl;
	myfile << size_array << std::endl;
	myfile << run_time << " seconds" << std::endl;

	if(h == unsorted) myfile << "random" << std::endl;
	else if(h == sorted) myfile << "Sorted" << std::endl;
	else if (h == inverted) myfile << "Inverted" << std::endl;
	myfile << "-----------------------------------------" << std::endl;
	myfile << "\n";
	myfile.close();
}

/**funktion f�r att generera ett randomiserat nummer mellan 0 och storleken */
int randtime::randomnumber()
{	
	std::uniform_int_distribution<int> dist(0,size_array);
	return dist(mt);
}

/**den virtuella funktion som g�r de olika sorteingmetoderna beroende p� vilken klass som k�rs*/
void randtime::min_sort(int* arr, int size)
{
}

/** visuallierar hela arrayen i ordnning fr�n index 0 till sista*/
void randtime::print_array()
{
	for (int i = 0; i<size_array; i++)
	{
		std::cout << arr[i] << std::endl;
	}
}
/**funktion f�r att ta bort dynamiskt allokerade arrayer*/
void randtime::delarr()
{
	delete[] arr;
	arr=nullptr;
}
