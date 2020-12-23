#include <iostream>

using namespace std;


template<class T>
struct Node
{
public:
	T value;
	Node<T>* next;
	Node(T value, Node<T>* next)
	{
		this->value = value;
		this->next = next;
	}
};


template<class T>
class Stack
{
	
};


template<class T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
	int count;
public:
	List();
	List(const List& list);
	~List();

	T& operator[](const int index);

	int getCount() const { return this->count; };
	void add(const T& value);
	T pop(int index);
	void clear();

	void print();
};	


template<class T>
List<T>::List()
{
	this->head = NULL;
	this->tail = NULL;
	this->count = 0;
}

template<class T>
List<T>::List(const List& list)
{
	Node<T>* node = list.head;
	if (node == NULL)
	{
		this->head = NULL;
		this->tail = NULL;
		this->count = 0;
		return;
	}

	while (node != NULL)
	{
		this->add(node->value);
		node = node->next;
	}
	this->count = list.count;
}

template <typename T>
List<T>::~List()
{
	this->clear();
}

template <typename T>
void List<T>::add(const T& value)
{
	Node<T>* node = new Node<T>(value, NULL);
	if (this->head == NULL)
		this->head = node;
	else
		this->tail->next = node;
	this->tail = node;
	this->count++;
}

template <typename T>
T List<T>::pop(int index)
{
	/* 
		¬озвращает удаленное значение
		”дал€етс€ так же, как беретс€ по индексу (начина€ с 0)
	*/
	if (index >= this->count)
		throw logic_error("List: Index out of the range");
	else
	{
		T val;
		if (index == 0)
		{
			val = this->head->value;
			this->head = this->head->next;

			return val;
		}
		int counter = 0;
		Node<T>* node = this->head;
		Node<T>* prev;
		while (counter != index)
		{
			prev = node;
			node = node->next;
			counter++;
		}

		val = node->value;
		Node<T>* temp = node->next;
		delete node;
		node = temp;
		prev->next = node;

		this->count--;

		return val;
	}
}

template <typename T>
void List<T>::clear()
{
	if (this->head != NULL)
	{
		Node<T>* node = this->head;
		Node<T>* next;
		while (node != NULL)
		{
			next = node->next;
			delete node;
			node = next;
		}
		this->head = NULL;
	}
	this->count = 0;
}

template <typename T>
T& List<T>::operator[](const int index)
{
	if (index >= this->count)
		throw logic_error("List: Index out of the range");
	else
	{
		int counter = 0;
		Node<T>* node = this->head;
		while (counter != index)
		{
			node = node->next;
			counter++;
		}

		return node->value;
	}
}

template <typename T>
void List<T>::print()
{
	if (this->count == 0)
	{
		cout << "List is empty" << endl;
		return;
	}

	Node<T>* node = this->head;
	cout << "[";
	while (node != NULL)
	{
		if (node->next == NULL)
		{
			cout << node->value << "]" << endl;
			return;
		}
		cout << node->value << ", ";
		node = node->next;
	}
}