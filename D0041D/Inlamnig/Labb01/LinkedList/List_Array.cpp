//#include "List_Array.h"
//#include <iostream>
//
//Node::Node()
//{
//	number = 0;
//	next = nullptr;
//}
//
//LinkedList::LinkedList(int size)
//{
//	head = new Node;
//	head->number = 0;
//	current = head->next;
//	previous = head;
//	max_size = size;
//}
//
////checks if Current* is a nullpointer. Used in forth() to not go out of bounds
//bool LinkedList::isOff()
//{
//	return current == nullptr;
//}
//
////returns the data stored in Node
//int LinkedList::item()
//{
//	return current->number;
//}
//
////Sets Current* to the first Node that contains data.
//void LinkedList::start()
//{
//	current = head;
//	current = current->next;
//	previous = head;
//}
//
////Previous points to the same Node that Current is pointing to and then set Current to the next Node
//void LinkedList::forth()
//{
//	if(isOff() == false)
//	{
//		previous = current;
//		current = previous->next;
//	}
//}
//
////To insert a new Node at the end of the list
//void LinkedList::insertBefore(int num)
//{
//	if (current_size < max_size)
//	{
//		Node* temp = new Node;
//		temp->number = num;
//		temp->next = current;
//		previous->next = temp;
//		previous = temp;
//		current_size += 1;
//	}
//
//}
//
////Removes the object where Current is pointing to
//void LinkedList::removeAt()
//{
//	Node* temp = current;
//	current = temp->next;
//	delete temp;
//	current_size -= 1;
//}
//
//
//
//
