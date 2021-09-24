#include "modern_handle.h"

modern_handle::modern_handle(modern_class* const obj) : m_object(new volatile modern_class*(obj)), m_num(new int64_t(1))
{

}

modern_handle::modern_handle(modern_handle& diff) : m_object(diff.m_object), m_num(diff.m_num)
{
	m_num[0]++;
}

void modern_handle::Release() const
{
	m_object[0] = nullptr;
}

modern_handle::~modern_handle()
{
	if (m_num[0] > 1)
	{
		m_object[0] = nullptr;
		delete m_num;
		delete m_object;
		m_num = nullptr;
		m_object = 0;
	}
	else
	{
		m_num[0]--;
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
