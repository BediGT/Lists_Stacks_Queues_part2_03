#pragma once
#include <iostream>
#include <string>

template<typename T>
class Stack {
	T* stack;
	int capacity;
    int numberOfElements;
public:
    Stack();
    Stack(const Stack<T>& other);
    ~Stack();

    void push(T element);
    T pop();
    T peek();
    bool isEmpty();

    void makeStack(std::string value);
    void printStack();
};