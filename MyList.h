#ifndef MyList_H
#define MyList_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template <typename T>
class Node
{
	private:
		T elem; //data element (type T in this case)
		Node<T>* next; //Link (pointer) to the next Node
		Node<T>* prev; //Link (pointer) to the previous Node
		template <typename T2> friend class HashList;
	public:
		Node(): next(NULL), prev(NULL) //empty constructor
		{}
		Node(T elem) : elem(elem), next(NULL), prev(NULL) //one argument constructor
		{}
};
//==============================================================
template <typename T>
class HashList
{
	private:
		Node<T>* head; 	// pointer to the head of List
		Node<T>* tail; 	// pointer to the tail of List
		int listsize; 	//size of the bucket/list
	public:
		HashList (); // empty list constructor
		~HashList (); // destructor to clean up all nodes
		void addBefore(Node<T> *ptr, const T& elem);	 //add a new node before ptr
		void addBack(const T & elem); //add a new node to the back of the list
		void remove(Node<T>* v); //remove a node at a position
		bool empty() const; //check if list is empty
		void removeFront(); //remove node at the front of the list
		int size(); // return the size of the bucket/list
		class iterator; //iterator class for traversing the list
		iterator begin()  
		{
			return iterator(head->next);
		}
		iterator end()
		{
			return iterator(tail);
		}
		class iterator
		{//complete the itereator class (which include iterator traits)
			private:
				Node<T>* v;
			public:
				using iterator_category = bidirectional_iterator_tag;
				using difference_type = ptrdiff_t;
				using value_type = T;
				using pointer = Node<T>*;
				using reference = Node<T>&;
			public:
				iterator(Node<T>* u)
				{
					v = u;
				}
				T& operator*()
				{
					return v->elem;
				}
				iterator& operator++()
				{
					v = v->next;
					return *this;
				}
				iterator& operator--()
				{
					v = v->prev;
					return *this;
				}
				bool operator!=(const iterator &other) const
				{
					return v != other.v;
				}
				bool operator==(const iterator &other) const
				{
					return v == other.v;
				}
				Node<T>* getkey()
				{
					return v;
				}
		};
	
};

#endif