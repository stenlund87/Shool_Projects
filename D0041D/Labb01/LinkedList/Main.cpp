#include "Unit_test.h"
//#include "Stack_v2.h"
#include <iostream>
#include "LinkedList.h"




void main()
{

	LLtester<int> unit_tester;
	LinkedList linked;
	LinkedList_Arr<int> arr(5);
	Queue<int> que;
	Stack<int> stack;

	//littletestofdoom(linked);
	//littletestofdoomforarray(arr);
	unit_tester.Start_Test(linked);
	unit_tester.Start_Test(arr);
	unit_tester.Start_Test(stack);
	unit_tester.Start_Test(que);
	getchar();
}