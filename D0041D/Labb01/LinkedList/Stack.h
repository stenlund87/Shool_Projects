#include "List_Array.h"
#include <stdexcept>

template<class T> class Stack
{
	public:
		Stack();
		~Stack();
		void Push(T in_data);
		void Pop();
		bool Empty_Check();
		T Get_Top();
		int Size();

	private:
		struct Node 
		{
			Node(){	data = 0; next = nullptr;}
			T data;
			Node* next;
		};
		Node* top;
		int num_elements;
};

template<class T>Stack<T>::Stack()
{
	top = nullptr;
	num_elements = 0;
}

template<class T>Stack<T>::~Stack()
{
}

template<class T>void Stack<T>::Push(T in_data)
{
	Node* new_top = new Node<T>();
	new_top->data = in_data;
	new_top->next = top;
	top = new_top;
	num_elements += 1;
}

template<class T>void Stack<T>::Pop()
{
	if(!Empty_Check())
	{
		Node* temp = top;
		top = top->next;
		delete temp;
		num_elements -= 1;
	}
}

template<class T>bool Stack<T>::Empty_Check()
{
	return top == nullptr;
}

template<class T>T Stack<T>::Get_Top()
{
	if(!Empty_Check())
	{
		return top->data;
	}
	throw std::range_error("The stack is empty");
}

template<class T>int Stack<T>::Size()
{
	return num_elements;
}