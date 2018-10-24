#include "LinkedList.h"
#include "Array_v2.h"
#include "Queue.h"

template<class T> class LLtester 
{
	public:


		/**
		*Adds a number between 0->value except for LinkedList_Arr
		*/
		void Add(LinkedList& ll, T value);
		void Add(LinkedList_Arr<T>& la, T value);
		void Add(Stack<T>& stack, T value);
		void Add(Queue<T>& que, T value);

		/**
		*Calls the methods to delete a node
		*/
		void Delete(LinkedList& ll);
		void Delete(LinkedList_Arr<T>& la);
		void Delete(Stack<T>& stack);
		void Delete(Queue<T>& que);

		/**
		*Method to set iteratorPos to the beginning of the list
		*/
		void Start(LinkedList& ll);
		void Start(LinkedList_Arr<T>& la);

		/**
		*Lets iteratorPos in LinkedList and LinkedList_Arr take a step forward in the list 
		*/
		void Step(LinkedList& ll);
		void Step(LinkedList_Arr<T>& la);
		/**
		*Prints out the value returned from each class.
		*/
		void Get(LinkedList& ll);
		void Get(LinkedList_Arr<T>& la);
		void Get(Stack<T>& stack);
		void Get(Queue<T>& que);

		//Functions that tests various things like deleting the first node
		/**
		*tries adds a value to the beginning
		*/
		void Add_Beginning(LinkedList& ll, T value);
		void Add_Beginning(LinkedList_Arr<T>& la, T value);

		/*
		*Special case. Adds a value at the end of List_Arr
		*@param LinkedList_Arr and a value
		*/
		void Add_More(LinkedList_Arr<T>& la, T value);

		/**
		*Goes to the beginning and try to delete that Node
		*@param takes a LinkedList or LinkedList_Arr as argument
		*LinkedList_Arr must be of the same type as LLtester
		*/
		void Delete_Beginning(LinkedList& ll);
		void Delete_Beginning(LinkedList_Arr<T>& la);

		/**
		*Calls forth() to the end +1 step
		*@Takes an list of type LinkedList or LinkedList_Arr
		**LinkedList_Arr must be of the same type as LLtester
		*/
		void Step_Test(LinkedList& ll);
		void Step_Test(LinkedList_Arr<T>& la);

		/**
		*Deletes all nodes +1 to see what happens
		*@param takes a class of the same type as argument
		*/
		void Delete_All(LinkedList& ll);
		void Delete_All(LinkedList_Arr<T>& la);
		void Delete_All(Stack<T>& stack);
		void Delete_All(Queue<T>& que);

		/**
		*Test to check most possible errors
		*Calls Step_Test, Delete_All, Add_Beginning and Get
		*@param takes a class of the same type as argument 
		*/
		void Start_Test(LinkedList& ll);
		void Start_Test(LinkedList_Arr<T>& la);
		void Start_Test(Stack<T>& stack);
		void Start_Test(Queue<T>& que);

};


template <class T>
void LLtester<T>::Add(LinkedList& ll,T value)
{
		ll.insertBefore(value);
}

template <class T>
void LLtester<T>::Add(LinkedList_Arr<T>& la,T value)
{
	try
	{
		la.insertBefore(value);
	}
	catch (const std::range_error& e)
	{
		std::cerr << e.what();
	}
}


template <class T>
void LLtester<T>::Add(Stack<T>& stack, T value)
{
		stack.Push(value);
}

template <class T>
void LLtester<T>::Add(Queue<T>& que, T value)
{
		que.Enqueue(value);

}

template <class T>
void LLtester<T>::Delete(LinkedList& ll)
{
	ll.removeAt();
}

template <class T>
void LLtester<T>::Delete(LinkedList_Arr<T>& la)
{
	la.removeAt();
}

template <class T>
void LLtester<T>::Delete(Stack<T>& stack)
{
	stack.Pop();
}

template <class T>
void LLtester<T>::Delete(Queue<T>& que)
{
	que.Dequeue();
}

template <class T>
void LLtester<T>::Start(LinkedList& ll)
{
	ll.start();
}

template <class T>
void LLtester<T>::Start(LinkedList_Arr<T>& la)
{
	la.start();
}


template <class T>
void LLtester<T>::Step(LinkedList& ll)
{
	ll.forth();
}

template <class T>
void LLtester<T>::Step(LinkedList_Arr<T>& la)
{
	la.forth();
}
template <class T>
void LLtester<T>::Get(LinkedList& ll)
{
	try
	{
		std::cout<< ll.item()<<std::endl;
	}
	catch(const std::range_error& e)
	{
		std::cerr << e.what();
	}
}

template <class T>
void LLtester<T>::Get(LinkedList_Arr<T>& la)
{
	try
	{
		std::cout<< la.item()<< std::endl;
	}
	catch(const std::range_error& e)
	{
		std::cerr << e.what();
	}
}

template <class T>
void LLtester<T>::Get(Stack<T>& stack)
{
	try
	{
		std::cout<< stack.Get_Top() <<std::endl;
	}
	catch (const std::range_error& e)
	{
		std::cerr << e.what();
	}
}

template <class T>
void LLtester<T>::Get(Queue<T>& que)
{
	try
	{
		std::cout<< que.Get_Front() <<std::endl;
	}
	catch (const std::range_error& e)
	{
		std::cerr << e.what();
	}
}


template <class T>
void LLtester<T>::Add_Beginning(LinkedList& ll, T value)
{
	try
	{
		ll.start();
		ll.insertBefore(value);
	}
	catch(const std::range_error& e)
	{
		std::cerr << e.what();
	}
}

template <class T>
void LLtester<T>::Add_Beginning(LinkedList_Arr<T>& la, T value)
{
	la.start();
	la.insertBefore(value);
}

template <class T>
void LLtester<T>::Add_More(LinkedList_Arr<T>& la, T value)
{
	int size = la.Max_Size();
	la.start();
	for(int i = 0; i<size; i++)
	{
		la.insertBefore(i);
		la.forth();
	}
	la.insertBefore(value);
}

template <class T>
void LLtester<T>::Delete_Beginning(LinkedList& ll)
{
	ll.start();
	ll.removeAt();
}

template <class T>
void LLtester<T>::Delete_Beginning(LinkedList_Arr<T>& la)
{
	la.start();
	la.removeAt();
}

template <class T>
void LLtester<T>::Step_Test(LinkedList& ll)
{
	int size = ll.Get_Size() + 1;
	for (int i = 0; i<size;i++)
	{
		ll.forth();
	}
}

template <class T>
void LLtester<T>::Step_Test(LinkedList_Arr<T>& la)
{
	int size = la.Get_Size(); + 1;
	for (int i = 0; i < size; i++)
	{
		la.forth();
	}
}

template <class T>
void LLtester<T>::Delete_All(LinkedList& ll)
{
	int size = ll.Get_Size() + 1;
	for (int i = 0; i < size; i++)
	{
		ll.removeAt();
	}
}

template <class T>
void LLtester<T>::Delete_All(LinkedList_Arr<T>& la)
{
	for (int i = 0; i<la.Get_Size()+1; i++)
	{
		la.removeAt();
	}
}

template <class T>
void LLtester<T>::Delete_All(Stack<T>& stack)
{
	int size = stack.Get_Size() + 1;
	for (int i = 0; i < size; i++)
	{
		stack.Pop();
	}
}

template <class T>
void LLtester<T>::Delete_All(Queue<T>& que)
{
	int size = que.Get_Size() + 1;
	for (int i = 0; i < size; i++)
	{
		que.Dequeue();
	}
}

template <class T>
void LLtester<T>::Start_Test(LinkedList& ll)
{
	std::cout << "-------------------------------------------"<< std::endl;
	std::cout << "We have now entered numbers between 1-6" << std::endl;
	for (int i = 1; i<6; i++)
	{
		ll.insertBefore(i);
	}
	ll.start();
	std::cout << "We now try to enter the number 45 to the beginning of the list"<< std::endl;
	std::cin.ignore();
	this->Add_Beginning(ll,45);
	std::cout << "We now try to go to the end of the list and beyond"<< std::endl;
	std::cin.ignore();
	this->Step_Test(ll);
	this->Start(ll);
	std::cout << "The number that should show is 45" << std::endl;
	this->Get(ll);
	std::cout << "We are now deleting the beginning of the list and two more Nodes" << std::endl;
	std::cin.ignore();
	this->Delete_Beginning(ll);
	this->Delete(ll);
	this->Delete(ll);
	std::cout << "The number that should show is 3" << std::endl;
	this->Get(ll);
	this->Delete_All(ll);
	std::cout << "We have now deleted all Nodes + 1" << std::endl;
	std::cout << "We should now get a range_error that say that we are at the end of the list" << std::endl;
	std::cout << "We shouldnt get a value returned to us" << std::endl;
	std::cin.ignore();
	this->Get(ll);
	std::cout << "Sucess!!!!" << std::endl;
	std::cout << "Press Enter to continue...." << std::endl;
	std::cin.ignore();
}


template <class T>
void LLtester<T>::Start_Test(LinkedList_Arr<T>& la)
{
	std::cout << "-------------------------------------------"<< std::endl;
	std::cout << "We have now entered numbers between 1 and the size of the array" << std::endl;
	for (int i = 1; i<la.Get_Size()+1; i++)
	{
		la.insertBefore(i);
	}
	la.start();
	std::cout << "We now try to enter the number 100 to the beginning list"<< std::endl;
	std::cout << "We should get a range_error that say that the stack is empty"<< std::endl;
	std::cin.ignore();
	this->Add_Beginning(la,100);
	this->Start(la);
	std::cout << "The number that should show is 1" << std::endl;
	this->Get(la);
	std::cout << "We are now deleting the beginning of the list" << std::endl;
	std::cin.ignore();
	this->Delete_Beginning(la);
	std::cout << "The number that should show is 2" << std::endl;
	this->Get(la);

	std::cout << "We are now trying to step outside of the array and beyond" << std::endl;
	this->Step_Test(la);
	std::cout << "Sucess!!!!" << std::endl;
	std::cout <<" " << std::endl;

	std::cout << "We now try deleted all Nodes + 1" << std::endl;
	this->Delete_All(la);

	std::cout << "We should now get a range_error that say that we are at the end of the list" << std::endl;
	std::cout << "We shouldnt get a value returned to us" << std::endl;
	std::cin.ignore();
	this->Get(la);
	std::cout << "Sucess!!!!" << std::endl;
	std::cout << "Press Enter to continue...." << std::endl;
	std::cin.ignore();
}

template <class T>
void LLtester<T>::Start_Test(Stack<T>& stack)
{
	std::cout << "-------------------------------------------"<< std::endl;
	std::cout << "We have now entered numbers between 1-5 to the stack" << std::endl;
	for (int i = 1; i<6; i++)
	{
		stack.Push(i);
	}
	std::cout << "We now enter the number 75 to top of the stack"<< std::endl;
	std::cin.ignore();
	this->Add(stack,75);
	std::cout << "The number that should show is 75" << std::endl;
	this->Get(stack);
	this->Delete(stack);
	std::cout << "The number that should show is 5" << std::endl;
	this->Get(stack);
	this->Delete_All(stack);
	std::cout << "We have now deleted the whole stack +1 element" << std::endl;
	std::cout << "We shouldnt get a value returned to us" << std::endl;
	std::cin.ignore();
	this->Get(stack);
	std::cout << "Sucess!!!!" << std::endl;
	std::cout << "Press Enter to continue...." << std::endl;
	std::cin.ignore();
}

template <class T>
void LLtester<T>::Start_Test(Queue<T>& que)
{
	std::cout << "-------------------------------------------"<< std::endl;
	std::cout << "We have now entered numbers between 1-5 to the Queue" << std::endl;
	for (int i = 1; i<6; i++)
	{
		que.Enqueue(i);
	}
	std::cout << "We now enter the number 99 to the back of the Queue"<< std::endl;
	std::cin.ignore();
	this->Add(que,99);
	std::cout << "The number that should show is 1" << std::endl;
	this->Get(que);
	std::cout << "We now delete the first to values from the Queue" << std::endl;
	this->Delete(que);
	this->Delete(que);
	std::cout << "The number that should show is 3" << std::endl;
	this->Get(que);
	this->Delete_All(que);
	std::cout << "We have now deleted the whole que +1 element" << std::endl;
	std::cout << "We shouldnt get a value returned to us" << std::endl;
	std::cin.ignore();
	this->Get(que);
	std::cout << "Sucess!!!!" << std::endl;
	std::cout << "Press Enter to continue...." << std::endl;
	std::cin.ignore();
}