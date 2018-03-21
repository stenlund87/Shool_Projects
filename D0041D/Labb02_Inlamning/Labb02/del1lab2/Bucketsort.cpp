#include "Bucketsort.h"
#include <vector>
#include <algorithm>
#include <iostream>;

/**konstruktor för bucketsort*/
Bucketsort::Bucketsort(int size)
{
	arr = new int[size];
	size_array = size;
	run_time=0;
}

/** funktion för att få namn av sorteringmetod/klass */
std::string Bucketsort::name()
{
	return "Bucketsort";
}

//Bucketsort::~Bucketsort(void)
//{
//}

/** sorteringmetoden för bcuketsort */
void Bucketsort::min_sort(int* arr,const int size)
{
	int n = ceil(float(size/10.0));
	std::vector<std::vector<int>> b(n+1);							///< vektorer med vektorer i sig för att agera buckets

	for(int i=0;i<size;i++)
	{
		int ind=floor(float(arr[i]/10));							///< Fixar ett index till bucketen talet i arr kommer att hamna i 
		b[ind].push_back(arr[i]);									///< push_back in i i vektorerna som agerar hink
	}
	for(int i=0;i<n;i++){sort(b[i].begin(),b[i].end());}			///< sorterar alla buckets
	int ind=0,i,j;
	for(i=0;i<n;i++)												
	for(j=0;j<b[i].size();j++){arr[ind++]=b[i][j];}
}