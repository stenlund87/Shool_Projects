#include <stdexcept>


template <class T> class LinkedList
{
	public:
		LinkedList(int size);
		~LinkedList();

		bool isOff();
		T item();
		void start();
		void forth();
		void insertBefore(T data);
		void removeAt();
		void whole();


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
				next = -1;
			}

			T data;
			int next;
		};

		void linker();
		Node* nodes;
		int free_list;
		int size;
};

template <class T>
LinkedList<T>::LinkedList(int size)
{
	this->nodes = new Node[size];
	this->size = size;
	this->free_list = 0;
	this->head = this->previous = -1;
	this->iteratosPos = 0;
	linker();
}

template <class T>
LinkedList<T>::~LinkedList()
{
	delete[] nodes;
}

template <class T>
bool LinkedList<T>::isOff()
{
	return iteratosPos == -1;
}

template <class T
>T LinkedList<T>::item()
{
	if(!isOff())
	{
		return nodes[iteratosPos].data;
	}
	throw std::range_error("You are at the end of the list");
}

template <class T>
void LinkedList<T>::start()
{
	iteratosPos = head;
	previous = -1;
}

template <class T>
void LinkedList<T>::forth()
{
	if(!isOff())
	{
		previous = iteratosPos;
		iteratosPos = nodes[previous].next;
	}
}

template <class T> 
void LinkedList<T>::insertBefore(T data)
{
	if(free_list >= 0)
	{
		previous = iteratosPos;
		iteratosPos = free_list;
		free_list = nodes[iteratosPos].next;
		nodes[iteratosPos].data = data;

		if(previous >= 0)
		{
			nodes[previous].next = iteratosPos;
		}
	}
}

template <class T> 
void LinkedList<T>::removeAt()
{

	if(previous >=0)
	{
		nodes[previous].next = nodes[iteratosPos].next;
	}

	if(iteratosPos == head)
	{
		head = nodes[iteratosPos].next;
	}

	nodes[iteratosPos].data = NULL;
	nodes[iteratosPos].next = free_list;
	free_list = iteratosPos;

	if(previous >=0)
	{
		iteratosPos = nodes[previous].next;
	}
	else
	{
 		iteratosPos = -1;
	}	
}

template <class T> 
void LinkedList<T>::linker()
{
	for(int i = 0; i<this->size-1; i++)
	{
		nodes[i].next = i+1;
	}
	nodes[size-1].next = -1;
}


template <class T> 
void LinkedList<T>::whole()
{
	for(int i = 0; i<this->size; i++)
	{
		std::cout << nodes[i].data << std::endl;
	}
}