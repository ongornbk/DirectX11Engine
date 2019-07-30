#pragma once
#include "IBidirectionalStruct.h"

template <class T>
class List : public IBidirectionalStruct<T>
{
public:

	struct ListElement : public IBidirectionalElement<T>
	{

		ListElement(const T element)
		{
			data = element;
			next = nullptr;
			previous = nullptr;
		}

		~ListElement()
		{
			if (next)
			{
				delete next;
				next = nullptr;
			}
		}


	};

	class IBidirectionalElement<T>* __head;
	class IBidirectionalElement<T>* __tail;

	int32 __size;

	List()
	{
		__head = nullptr;
		__tail = nullptr;
		__size = 0;
	}
	~List()
	{
		if (__head)
		{
			delete __head;
			__head = nullptr;
		}
	}

	void push_back(const T element) override
	{
		if (__head)
		{
			__tail->next = new struct ListElement(element);
			class IBidirectionalElement<T>* prev = __tail;
			__tail = __tail->next;
			__tail->previous = prev;
		}
		else
		{
			__head = new struct ListElement(element);
			__tail = __head;
		}
		__size++;
	}

	void push_front(const T element) override
	{
		if (__head)
		{
			__head->previous = new struct ListElement(element);
			class IBidirectionalElement<T>* next = __head;
			__head = __head->previous;
			__head->next = next;
		}
		else
		{
			__head = new struct ListElement(element);
			__tail = __head;
		}
		__size++;
	}

	T& get_front() const override
	{
		assert(__head);
		return __head->data;
	}

	T& get_back() const override
	{
		assert(__tail);
		return __tail->data;
	}

	void pop_front()
	{
		assert(__head);
		class IBidirectionalElement<T>* pop = __head;
		__head = __head->next;
		pop->next = nullptr;
		delete pop;
		__size--;
	}

	void pop_back()
	{
		assert(__tail);
		class IBidirectionalElement<T>* pop = __tail;
		__tail = __tail->previous;
		pop->next = nullptr;
		delete pop;
		__size--;
	}

	int32 size() const override
	{
		return __size;
	}

	bool empty() const override
	{
		if (__size)
			return false;
		else return true;
	}

	IBidirectionalElement<T>* front() const override
	{
		return __head;
	}

	IBidirectionalElement<T>* end() const override
	{
		return __tail;
	}

	void erase(const int32 index)
	{
		class IBidirectionalElement<T>* curr = __head;
		if (__head)
		{
			for (int32 i = 0; i < index; ++i)
			{
				curr = __head->next;
				if (!curr)
					return;
			}
			curr->next->previous = curr->previous;
			curr->previous->next = curr->next;
			delete curr;
			curr = nullptr;
		}
		else
		{
			return;
		}
	}
};