#include "LinkedList.h"
#include <iostream>

void main()
{
	LinkedList test;
	test.insertBefore(1);
	test.insertBefore(2);
	test.insertBefore(3);
	test.insertBefore(4);
	test.insertBefore(5);

	test.start();
	test.forth();
	test.forth();
	test.forth();
	std::cout << test.item() << std::endl;
	test.forth();
	std::cout << test.item() << std::endl;
	test.forth();
	test.forth();
	test.start();
	test.forth();
	std::cout << test.item() << std::endl;
	test.removeAt();
	std::cout << test.item() << std::endl;
}