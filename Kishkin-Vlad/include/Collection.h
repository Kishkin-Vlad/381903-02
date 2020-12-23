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
private:
	T* pStack;
	int size;
	int top;
public:
	Stack(int size = 100);
	Stack(const Stack<T>& s);
	~Stack();

	Stack<T>& operator=(const Stack<T>& s);
	bool operator==(const Stack<T>& s);

	int getSize() const { return this->size; };
	int getTopIndex() const { return this->top; };

	void add(const T& value); // add value in top
	T pop(); // del top element

	bool isFull() { return (size - 1 == top); };
	bool isEmpty() { return (top == -1); };

	void clear();

	void print();
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


/*               ----------------------------------Stack----------------------------------              */
template<class T>
Stack<T>::Stack(int size = 100)
{
	if (size <= 0)
		throw logic_error("Stack: size should be > 0");
	top = -1;
	this->size = size;
	pStack = new T[this->size];
}

template<class T>
Stack<T>::Stack(const Stack<T>& s)
{
	size = s.size;
	pStack = new T[size];
	if (s.top == -1)
		return;

	top = s.top;
	for (int i = 0; i <= top; i++)
		pStack[i] = s.pStack[i];
}

template<class T>
Stack<T>::~Stack()
{
	this->clear();
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
	if (this == &s)
		return *this;
	delete[] pStack;

	size = s.size;
	pStack = new T[size];
	if (s.top == -1)
		return *this;

	for (int i = 0; i <= top; i++)
		pStack[i] = s.pStack[i];

	return *this;
}

template<class T>
bool Stack<T>::operator==(const Stack<T>& s)
{
	if (size != s.size || top != s.top)
		return false;

	for (int i = 0; i <= top; i++)
		if (pStack[i] != s.pStack[i])
			return false;

	return true;
}

template<class T>
void Stack<T>::add(const T& value)
{
	if (this->isFull())
		throw logic_error("Stack: is overflow");
	
	top++;
	pStack[top] = value;
}

template<class T>
T Stack<T>::pop()
{
	if (this->isEmpty())
		throw logic_error("Stack: is empty");
	
	T value = pStack[top];
	top--;

	return value;
}

template<class T>
void Stack<T>::clear()
{
	top = -1;
	size = 0;
	delete[] pStack;
	pStack = 0;
}

template <typename T>
void Stack<T>::print()
{
	if (this->top == -1)
	{
		cout << "Stack: is empty" << endl;
		return;
	}

	cout << "[";
	for (int i = 0; i < top; i++)
		cout << pStack[i] << ", ";
	cout << pStack[top] << "]";
}


/*               ----------------------------------List----------------------------------              */
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
		return deleted element
		begin with 0 (as operator[])	
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
		cout << "List: is empty" << endl;
		return;
	}

	Node<T>* node = this->head;
	cout << "[";
	while (node != NULL)
	{
		if (node->next == NULL)
		{
			cout << node->value << "]";
			return;
		}
		cout << node->value << ", ";
		node = node->next;
	}
}