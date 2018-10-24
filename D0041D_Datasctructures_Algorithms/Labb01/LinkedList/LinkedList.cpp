#include "LinkedList.h"
#include <stdexcept>
#include <iostream>

Node::Node()
{
	number = 0;
	next = nullptr;
}


LinkedList::LinkedList()
{
	head = new Node;
	head->number = 0;
	current = head->next;
	previous = head;
	list_size = 0;
}

LinkedList::~LinkedList()
{
	this->start();
	for(int i = 0; i<list_size; i++)
	{
		this->removeAt();
	}
	delete head;
}

//checks if Current* is a nullpointer. Used in forth() to not go out of bounds
bool LinkedList::isOff()
{
	return current == nullptr;
}

//returns the data stored in Node
int LinkedList::item()
{
	if(!isOff())
	{
		return current->number;
	}
	throw std::range_error("You are at the end of the list\n");
}

//Sets Current* to the first Node that contains data.
void LinkedList::start()
{
	current = head->next;
	previous = head;
}

//Previous points to the same Node that Current is pointing to and then set Current to the next Node
void LinkedList::forth()
{
	if(!isOff())
	{
		previous = current;
		current = previous->next;
	}
}

//To insert a new Node at the end of the list
void LinkedList::insertBefore(int num)
{
	Node* temp = new Node;
	temp->number = num;
	temp->next = current;
	previous->next = temp;
	previous = temp;
	list_size += 1;
}

//Removes the object where Current is pointing to
void LinkedList::removeAt()
{
	if(!isOff())
	{
		Node* temp = current;
		current = temp->next;
		previous->next = current;
		delete temp;
		list_size -=1 ;
	}
}

int LinkedList::Get_Size()
{
	return list_size;
}




