#include <stdexcept>
#include "Stack_v2.h"


template <class T> class LinkedList_Arr : public Stack<int>
{
	public:
		LinkedList_Arr(int size);
		~LinkedList_Arr();

		/**
		*Checks if iteratorPos == -1
		*@Return true/false
		*/
		bool isOff();
		/**
		*Cheks isOff() if iteratorPos is -1
		@Return data if false
		*Throws a std::range_error if true
		*/
		T item();
		/**
		*Sets iteratorPos = head
		*Sets previous = -1
		*/
		void start();
		/**
		*Lets iteratorPos to take a step forward in the list
		*/
		void forth();
		/**
		*Gets an index from free_nodes and sets the value
		*If free_nodes is empty the Stack throws a range_error and this method catches it
		*/
		void insertBefore(T data);
		/**
		*Removes the data from the Node that iteratorPos is "pointing to"
		*/
		void removeAt();
		/**
		*Garbage method to return all values in the array
		*/
		void whole();
		/**
		*Garbage
		*/
		int& size();
		/**
		*Function for unit tester
		*/
		int& Get_Size();

	protected:
		int head;
		int iteratosPos;
		int previous;

	private:
		struct Node
		{
			Node() 
			{
				this->data = NULL; 
				next = -2;
			}

			T data;
			int next;
		};

		void linker();
		Stack <int> free_nodes; //Stack that keeps track of free index
		Node* nodes;
		int max_size;
		int current_size;
};

//Contructor that sets the size of the array
template <class T>
LinkedList_Arr<T>::LinkedList_Arr(int size)
{
	this->nodes = new Node[size];
	this->current_size = 0;
	this->max_size = size;
	this->head = this->previous = iteratosPos = -1;
	linker();
}


template <class T>
LinkedList_Arr<T>::~LinkedList_Arr()
{
	delete[] nodes;
}

//Checks if the position of the iterator is at the end of the array
template <class T>
bool LinkedList_Arr<T>::isOff()
{
	return iteratosPos == -1;
}

//Returns the data from the Node that iteratorPos is at and throws a range_error if it is at the end of the list
template <class T
>T LinkedList_Arr<T>::item()
{
	if(!isOff())
	{
		return nodes[iteratosPos].data;
	}
	throw std::range_error("You are at the end of the list\n");
}

//Sets iteratorPos to the beginning of the array
template <class T>
void LinkedList_Arr<T>::start()
{
	iteratosPos = head;
	previous = -1;
}

//Makes iteratorPos take a step forward in the array
template <class T>
void LinkedList_Arr<T>::forth()
{
	if(!isOff())
	{
		previous = iteratosPos;
		iteratosPos = nodes[previous].next;
	}
}

//Inserts/Changes the data at the index that iteratorPos "points" to
template <class T> 
void LinkedList_Arr<T>::insertBefore(T data)
{
	try
	{
		int indx = free_nodes.Get_Top();
		nodes[indx].data = data;
		nodes[indx].next = iteratosPos;

		if(previous == -1)
		{	
			head = indx;
		}
		else
		{
			nodes[previous].next = indx;
		}
		previous = indx;
		free_nodes.Pop();
		current_size += 1;
	}
	catch(std::range_error& e)
	{
		std::cerr << e.what();
	}
}

//Removes the data from the Node that iteratorPos "points" to
template <class T> 
void LinkedList_Arr<T>::removeAt()
{
	if(!isOff())
	{
		if(previous == -1)
		{
			head = nodes[iteratosPos].next;	
		}
		else
		{
			nodes[previous].next = nodes[iteratosPos].next;
		}
		if(head == iteratosPos)
		{
			head = nodes[head].next;
		}

		int temp = nodes[iteratosPos].next;
		nodes[iteratosPos].data = NULL;
		nodes[iteratosPos].next = -1;
		free_nodes.Push(iteratosPos);
		iteratosPos = temp;
		current_size -= 1;
	}
}

//Fills the stack with all free index
template <class T> 
void LinkedList_Arr<T>::linker()
{
	for(int i = max_size-1; i>-1; i--)
	{
		free_nodes.Push(i);
	}
}

//Prints all the data currently in the array
template <class T> 
void LinkedList_Arr<T>::whole()
{
	for(int i = 0; i<this->max_size; i++)
	{
		std::cout << nodes[i].data << std::endl;
	}
}

template <class T>
int& LinkedList_Arr<T>::size()
{
	return current_size;
}

template <class T>
int& LinkedList_Arr<T>::Get_Size()
{
	return max_size;
}