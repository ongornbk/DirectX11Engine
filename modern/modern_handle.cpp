#include "modern_handle.h"
#include <iostream>

void modern_handle::make_handle(modern_class* const obj)
{
	m_object = new (volatile modern_class*);
	m_num = new int64_t;
	m_object[0] = obj;
	m_num[0] = 1;
}

modern_handle::modern_handle()
{
	m_num = nullptr;
	m_object = nullptr;
}

void modern_handle::make_handle(const modern_handle& diff)
{
	m_object = diff.m_object;
	m_num = diff.m_num;
	m_num[0]++;
	//std::cout << m_num[0] - 1 << "::. " << m_num[0] << std::endl;
}

void modern_handle::Release() const
{
	m_object[0] = nullptr;
}

modern_handle::~modern_handle()
{
	//std::cout << "~modern_handle()" << std::endl;
	if (m_num[0] <= 1)
	{
		m_object[0] = nullptr;
		m_num[0] = 0;
		delete m_num;
		delete m_object;
		m_num = nullptr;
		m_object = 0;
	//	std::cout << "delete handle" << std::endl;
	}
	else
	{
		m_num[0]--;
	//	std::cout << (m_num[0])+1 << "::. " << m_num[0] << std::endl;
	}
}

volatile modern_class* modern_handle::operator->()
{
	return m_object[0];
}

volatile modern_class* modern_handle::get()
{
	return m_object[0];
}
