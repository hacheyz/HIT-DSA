/* 栈的类模板实现 */

#ifndef LAB2_STACK_H
#define LAB2_STACK_H

#include <iostream>
#include <cstring>

#define MAX_SIZE 500

template<typename T>
class Stack
{
private:
	T data[MAX_SIZE];
	int top;
public:
	Stack();
	~Stack();
	bool isEmpty();
	bool isFull();
	void push(T x);
	T pop();
	T getTop();
	void travel();
};

template<typename T>
Stack<T>::Stack()
{
	top = -1;
}

template<typename T>
Stack<T>::~Stack()
{
	top = -1;
}

template<typename T>
bool Stack<T>::isEmpty()
{
	return top == -1;
}

template<typename T>
bool Stack<T>::isFull()
{
	return top == MAX_SIZE - 1;
}

template<typename T>
void Stack<T>::push(T x)
{
	if (!isFull())
	{
		data[++top] = x;
	}
	else
	{
		std::cout << "栈满" << std::endl;
		exit(1);    // 栈满，错误码 1
	}
}

template<typename T>
T Stack<T>::pop()
{
	if (!isEmpty())
	{
		return data[top--];
	}
	else
	{
		std::cout << "栈空" << std::endl;
		exit(2);    // 栈空，错误码 2
	}
}

template<typename T>
T Stack<T>::getTop()
{
	if (!isEmpty())
	{
		return data[top];
	}
	else
	{
		std::cout << "栈空" << std::endl;
		exit(2);    // 栈空，错误码 2
	}
}

template<typename T>
void Stack<T>::travel()
{
	for (int i = 0; i < top + 1; ++i)
	{
		std::cout << data[i] << ' ';
	}
	std::cout << std::endl;
}

#endif //LAB2_STACK_H
