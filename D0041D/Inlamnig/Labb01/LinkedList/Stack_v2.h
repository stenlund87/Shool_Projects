#include <stdexcept>

template<class T> 
class Stack
{
	public:
		Stack();
		~Stack();

		/**
		*Creates a new Node and sets the value
		*Points top to the new Node
		*/
		void Push(T in_data);
		/**
		*Removes the Node and repoints top to its next
		*/
		void Pop();
		/**
		*Method to check if the stack is empty
		*@return true/false
		*/
		bool Empty_Check();
		/**
		*Checks isOff() and returns the value of top if false
		*Throws std::range_error if the Stack is empty
		*/
		T Get_Top();
		int& Get_Size();

	private:
		struct Node 
		{
			Node(){next = nullptr;}
			T data;
			Node* next;
		};
		Node* top;
		int num_elements;
};


template<class T>
Stack<T>::Stack()
{
	top = nullptr;
	num_elements = 0;
}

template <class T>
Stack<T>::~Stack()
{
	for(int i = 0; i<= num_elements; i++)
	{
		this->Pop();
	}
}


//Put a new Node at the top of the Stack
template<class T>
void Stack<T>::Push(T in_data)
{
	Node* new_top = new Node;
	new_top->data = in_data;
	new_top->next = top;
	top = new_top;
	num_elements += 1;
}

//Removes the top Node from the Stack
template<class T>
void Stack<T>::Pop()
{
	if(!Empty_Check())
	{
		Node* temp = top;
		top = top->next;
		delete temp;
		num_elements -= 1;
	}
}

//Checks if the Stack is empty (top pointer is nullptr)
template<class T>
bool Stack<T>::Empty_Check()
{
	return top == nullptr;
}

//Returns the data from the top Node of the Stack
template<class T>
T Stack<T>::Get_Top()
{
	if(!Empty_Check())
	{
		return top->data;
	}
	throw std::range_error("The stack is empty\n");
}

//Returns the size of the Stack (number of Nodes currently in it)
template<class T>
int& Stack<T>::Get_Size()
{
	return num_elements;
}