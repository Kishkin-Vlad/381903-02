#include <iostream>

using namespace std;


template<class T>
class ICollection
{
public:
	virtual ~ICollection() {};             // to call destructors correctly

	virtual int getSize() = 0;
	virtual T pop() = 0;
	virtual void add(const T& value) = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int find(const T& t) = 0;
	virtual int rfind(const T& t) = 0;
	virtual const T getLast() = 0;
	virtual void print() = 0;

	virtual T& operator[](const int index) = 0;
};


template<class T>
class Stack : public ICollection<T>
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
	T& operator[](const int index);

	int getFullSize() { return size; };             // get reality size
	int getSize() { return top + 1; };              // get stack's size

	void add(const T& value);                       // add value in top
	T pop();                                        // del top element and return him
	int find(const T& t);                           // find elem in list
	int rfind(const T& t);                          // reverse find elem in list
	const T getLast();                              // get top elem

	bool isFull() { return (size - 1 == top); };    // check if it is full
	bool isEmpty() { return (top == -1); };         // check if it is empty

	void clear();
	void print() { cout << *this; };

	friend ostream& operator<<(ostream& out, const Stack& stack)
	{
		if (stack.top == -1)
		{
			out << "Stack()" << endl;
			return out;
		}

		out << "Stack(";
		for (int i = 0; i < stack.top; i++)
			out << stack.pStack[i] << ", ";
		out << stack.pStack[stack.top] << ")";

		return out;
	}
};


template<class T>
class Node
{
public:
	T value;
	Node<T>* next;
	Node(T value, Node<T>* next)
	{
		this->value = value;
		this->next = next;
	}

	friend ostream& operator<<(ostream& out, const T& t)
	{
		out << t.value;

		return out;
	}
};


template<class T>
class List : public ICollection<T>
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

	int getSize() { return count; };               // get list's count
	void add(const T& value);                      // add elem in tail
	T pop(int index);                              // del elem by index (and return him)
	T pop();                                       // del last elem
	int find(const T& t);                          // find elem in list
	int rfind(const T& t);                         // reverse find elem in list
	const T getLast();

 	bool isEmpty() { return (head == NULL); };     // check if it is empty

	void clear();
	void print() { cout << *this; };

	friend ostream& operator<<(ostream& out, const List& list)
	{
		if (list.count == 0)
		{
			out << "List()" << endl;
			return out;
		}

		Node<T>* node = list.head;
		out << "List(";
		while (node != NULL)
		{
			if (node->next == NULL)
			{
				out << node->value << ")";
				return out;
			}
			out << node->value << ", ";
			node = node->next;
		}
	}
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
T& Stack<T>::operator[](const int index)
{
	return pStack[index];
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
int Stack<T>::find(const T& t)
{
	for (int i = 0; i < size; i++)
		if (t == pStack[i])
			return i;

	return -1;
}

template<class T>
int Stack<T>::rfind(const T& t)
{
	int index = -1;
	for (int i = 0; i < size; i++)
		if (t == pStack[i])
			index = i;

	return index;
}

template<class T>
const T Stack<T>::getLast()
{
	if (this->isEmpty())
		throw logic_error("Stack: is empty");

	T value = pStack[top];

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
		if (node == NULL)
			this->tail = node;
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
T List<T>::pop()
{
	/*
		return deleted last element
	*/
	
	return (this->pop(count - 1));
}

template<class T>
int List<T>::find(const T& t)
{
	Node<T>* node = this->head;

	for (int i = 0; i < count; i++)
	{
		if (t == node->value)
			return i;

		node = node->next;
	}

	return -1;
}

template<class T>
int List<T>::rfind(const T& t)
{
	Node<T>* node = this->head;
	int index = -1;
	for (int i = 0; i < count; i++)
	{
		if (t == node->value)
			index = i;

		node = node->next;
	}

	return index;
}

template<class T>
const T List<T>::getLast()
{
	return (this->tail->value);
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