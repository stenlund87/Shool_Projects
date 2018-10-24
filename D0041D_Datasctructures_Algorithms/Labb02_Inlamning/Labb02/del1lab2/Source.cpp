#include "randtime.h"
#include "Insertionsort.h"
#include "quicksort.h"
#include <iostream>
#include "Heapsort.h"
#include "Bucketsort.h"

#include <chrono>
#include "randtime.h"
#include "Vector_Heap.h"
#include "Vector_Rand.h"
#include "Vector_Bucket.h"
#include "Vector_Insertion.h"
#include "Vector_Quick.h"
using namespace std;


int main()
{

	try
	{
		int i=1000;
		while (i<1000001)
		{
			Insertionsort yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.delarr();			
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while ((i<1000001))
		{
			Vector_Insertion yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}

	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (i<1000001)
		{
			Insertionsort yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while ((i<1000001))
		{
			Vector_Insertion yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
		try
	{
		int i=1000;
		while (i<1000001)
		{
			Insertionsort yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while ((i<1000001))
		{
			Vector_Insertion yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	try
	{
		int i=1000;
		while (true)
		{
			quicksort yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Quick yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
		try
	{
		int i=1000;
		while (true)
		{
			quicksort yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Quick yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
		try
	{
		int i=1000;
		while (true)
		{
			quicksort yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Quick yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	try
	{
		int i=1000;
		while (true)
		{
			Heapsort yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Heap yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Heapsort yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Heap yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Heapsort yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Heap yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	try
	{
		int i=1000;
		while (true)
		{
			Bucketsort yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Bucket yay(i);
			yay.fillrandom();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Bucketsort yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Bucket yay(i);
			yay.fillinvert();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Bucketsort yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.delarr();
		}

		
	}
	catch(bad_alloc){}
	try
	{
		int i=1000;
		while (true)
		{
			Vector_Bucket yay(i);
			yay.fillsort();
			yay.runtime();
			i = i*10;
			yay.vecdel();
		}

		
	}
	catch(bad_alloc){}
	

	

}
