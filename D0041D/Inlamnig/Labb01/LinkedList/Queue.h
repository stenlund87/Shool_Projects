

template <class T> class Queue
{
	public:
		Queue();
		~Queue();

		/*
		*Creates a new node and sets the value
		*@param Data of the same type as the queue was created with
		*/
		void Enqueue(T in_data);
		/*
		*Removes the Node that front* is pointing to 
		*Sets front to front->next
		*/
		void Dequeue();
		/*
		*Returns the value of the Node that front is pointing to
		*/
		T Get_Front();
		/*
		*Method for unit tester
		*@return Returns the number of Nodes currently in the Queue
		*/
		int& Get_Size();

	private:
		struct Node 
		{
			Node(){	data = 0; next = nullptr;}
			T data;
			Node* next;
		};

		Node* front;
		Node* back;
		int queue_size;
};


template<class T>Queue<T>::Queue()
{
	front = nullptr;
	back = nullptr;
	queue_size = 0;
}

template <class T>Queue<T>::~Queue()
{
	for(int i = 0; i<=queue_size; i++)
	{
		this->Dequeue();
	}
}
template<class T>void Queue<T>::Enqueue(T in_data)
{
	if(front == nullptr)
	{
		front = new Node;
		front->data = in_data;
		back = front;
	}

	else
	{
		Node* temp = new Node;
		temp->data = in_data;
		back->next = temp;
		back = temp;
	}
	queue_size += 1;
}

template<class T>void Queue<T>::Dequeue()
{
	if(front != nullptr)
	{
		Node* temp = front;
		front = front->next;

		if(back == temp)
		{
			back = nullptr;
		}
		delete temp;
		queue_size -= 1;
	}

}

template<class T>T Queue<T>::Get_Front()
{
	if (front != nullptr)
	{
		return front->data;
	}
	throw std::range_error ("The queue is empty\n");
}

template <class T>int& Queue<T>::Get_Size()
{
	return queue_size;
}