#pragma once

template <class T>
struct StackElement
{
	T data;
	StackElement* next;

	StackElement() = delete;
	StackElement(T t) : data(t)
	{

	}
};

template <class T>
class Stack
{
	StackElement* __top;

public:

	void push(T t)
	{
		StackElement* temp = __top;
		__top = new StackElement(t);
		__top->next = temp;
	}

	void pop
	{
		if (__top)
		{
			StackElement* temp = __top.next;
			delete __top;
			__top = temp;
		}
	}

		T top()
	{
		if (__top)
		{
			return __top.data;
		}
		else
		{
			return (T)0;
		}
	}
};

