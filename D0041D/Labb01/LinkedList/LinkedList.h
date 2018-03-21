#pragma once

struct Node 
{
		Node();

		int number;
		Node* next;
};


class LinkedList
{
	public:
		LinkedList();
		~LinkedList();

		/**
		*Checks if current == nullptr
		*@Return true/false
		*/
		bool isOff();
		/**
		*Checks ifOff()
		*@Returns the value of the Node that current is pointing to
		*/
		int item();
		/**
		*Points current to heads Nodes next
		*Points previous to the same Node as head
		*/
		void start();
		/**
		*Points current and previous a to Nodes next
		*/
		void forth();
		/**
		*Inserts a new Node between current and previous
		*Points the new Nodes next to current
		*Points previous next to the new Node
		*Points previous to the new Node
		*/
		void insertBefore(int num);
		/**
		*Calls isOff() and goes forth is false
		*Removes the Node that current is pointing to and repoints current to its next
		*Points previous next to "new" current
		*/
		void removeAt();
		/**
		*Method that is used in unit tester
		*/
		int Get_Size();

	protected:
		Node* head;
		Node* current;
		Node* previous;
		int list_size;
};

