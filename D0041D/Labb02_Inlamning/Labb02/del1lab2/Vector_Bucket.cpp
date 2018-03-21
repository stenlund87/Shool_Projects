#include "Vector_Bucket.h"
#include <vector>
#include <algorithm>
#include <iostream>;

/** konstruktor för VEctor_bucket*/
Vector_Bucket::Vector_Bucket(int size)
{
	std::vector<int>*temp = new std::vector<int>(size,0);
	vec = temp;
	vec_size = size;
	run_time=0;
}

/** funktion för att returnera namn på sorteringsmetod/klass*/
std::string Vector_Bucket::name()
{
	return "Vector_Bucket";
}

//Vector_Bucket::~Vector_Bucket(void)
//{
//}

/** sorteringmetoden som används i Vector_bucket*/
void Vector_Bucket::min_sort(std::vector<int>* vec,const int size)
{
	int n = ceil(float(size/10));
	std::vector<std::vector<int>> b(n+1);			///<Skapar buckets

	for(int i=0;i<size;i++)
	{
		int ind=floor(float(vec->at(i)/10));
		b[ind].push_back(vec->at(i));
	}

	for(int i=0;i<n;i++){sort(b[i].begin(),b[i].end());}
	int ind=0,i,j;
	for(i=0;i<n;i++)
	for(j=0;j<b[i].size();j++){vec->at(ind++)=b[i][j];}
}