#include "Stack.h"

Whoops::Stack::Stack()
{
	m_top = nullptr;
	m_size = 0;
}

Whoops::Stack::~Stack()
{
	if (m_top)
	{
		delete m_top;
		m_top = nullptr;
	}
}

void * Whoops::Stack::top()
{
	return m_top->data;
}

void Whoops::Stack::pop()
{
	StackElement* temp = m_top->next;
	m_top->next = nullptr;
	delete m_top;
	m_top = temp;
	m_size--;
}

bool Whoops::Stack::empty()
{
	return !(bool)m_top;
}

void Whoops::Stack::push(void * element)
{
	if (m_top)
	{
		StackElement* niu = new StackElement();
		niu->data = element;
		niu->next = m_top;
		m_top = niu;
	}
	else
	{
		m_top = new StackElement();
		m_top->data = element;
	}
	m_size++;
}

void Whoops::Stack::clear()
{
	while (m_top)
	{
		pop();
	}
}

uint32_t Whoops::Stack::size()
{
	return m_size;
}
