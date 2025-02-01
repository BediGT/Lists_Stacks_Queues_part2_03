#include "MyStack.h"

template <typename T>
Stack<T>::Stack()
	:stack(new T[2]), capacity(2), numberOfElements(0)
{}

template <typename T>
Stack<T>::Stack(const Stack<T>& other)
{
	capacity = other.capacity;
	numberOfElements = other.numberOfElements;
	stack = new T[capacity];

	for (int i = 0; i < numberOfElements; i++)
	{
		stack[i] = other.stack[i];
	}
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] stack;
}

template <typename T>
void Stack<T>::push(T element)
{	
	if (numberOfElements >= capacity)
	{
		capacity *= 2;
		T* newStack = new T[capacity];
		for (int i = 0; i < numberOfElements; i++)
			newStack[i] = stack[i];
		delete[] stack;
		stack = newStack;
	}

	stack[numberOfElements] = element;

	numberOfElements++;
}


template <typename T>
T Stack<T>::pop()
{
	T temporary = stack[numberOfElements-1];

	numberOfElements--;

	return temporary;
}

template <typename T>
T Stack<T>::peek()
{
	return stack[numberOfElements-1];
}

template <typename T>
bool Stack<T>::isEmpty()
{
	if (numberOfElements == 0)
		return true;
	else
		return false;
}

template <typename T>
void Stack<T>::makeStack(std::string value)
{
	for (int i = 0; i < value.size(); i++)
	{
		if (value[i] == ' ') continue;
		push(value[i]);
	}
}

template <typename T>
void Stack<T>::printStack()
{
	for (int i = 0; i < numberOfElements; i++)
		std::cout << stack[i] << "\n";
}

template class Stack<int>;
template class Stack<float>;
template class Stack<double>;
template class Stack<char>;