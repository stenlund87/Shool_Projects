#pragma once
#include "Quadtree.h"
#include <iostream>


void main()
{
	std::vector<QuadTreeElement<float>> tjabba;
	QuadTree<QuadTreeElement<float>> hej;
	hej.Setup(15,15);
	QuadTreeElement<float> x1(4,4,1);
	QuadTreeElement<float>x2(5,2,2);
	QuadTreeElement<float>x3(5,1,4);
	QuadTreeElement<float>x4(8,3,5);
	QuadTreeElement<float>x5(17,1,6);
	QuadTreeElement<float>x6(0,20,7);
	hej.InsertElement(x1);
	hej.InsertElement(x2);
	hej.InsertElement(x3);
	hej.InsertElement(x4);
	hej.InsertElement(x5);
	hej.Setup(8,8);
	hej.InsertElement(QuadTreeElement<float>(1,1,14.5));
	hej.InsertElement(QuadTreeElement<float>(7,3,234.1));
	hej.InsertElement(QuadTreeElement<float>(2,2,7));
	hej.InsertElement(QuadTreeElement<float>(9,9,8));
	hej.FindElement(2,2,15,15,tjabba);

	for(int i = 0; i<tjabba.size();i++)
	{
		std::cout << tjabba[i].data << std::endl;
	}

}