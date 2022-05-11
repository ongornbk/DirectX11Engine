#include "modern_handle.h"
#include "modern_class_view.h"
#include <iostream>

modern_handle& modern_handle::operator=(modern_handle const& diff)
{
	if (m_object)
	{
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
	m_object = diff.m_object;
	m_num = diff.m_num;
	m_num[0]++;

	return*this;
}

bool modern_handle::operator<(const modern_handle& rhs)
{
	return m_object[0] < rhs.m_object[0];
}

void modern_handle::make_handle(
	struct modern_class* const obj
)
{
	m_object = new (volatile struct modern_class*);
	m_num = new int64_t;
	m_object[0] = obj;
	m_num[0] = 1;
}

void modern_handle::make_handle(
	volatile struct modern_class* const obj
) volatile
{
	m_object = new (volatile struct modern_class*);
	m_num = new int64_t;
	m_object[0] = obj;
	m_num[0] = 1;
}

modern_handle::modern_handle()
{
	m_num = nullptr;
	m_object = nullptr;
}

modern_handle::modern_handle(const modern_handle& diff)
{
	m_object = diff.m_object;
	m_num = diff.m_num;
	m_num[0]++;
}

modern_handle::modern_handle(modern_class_view& view)
{
	m_object = view.GetHandle().m_object;
	m_num = view.GetHandle().m_num;
	m_num[0]++;
}

void modern_handle::make_handle(
	const class modern_handle& diff
)
{
	if (m_object)
	{
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
	m_object = diff.m_object;
	m_num = diff.m_num;
	m_num[0]++;

	//std::cout << m_num[0] - 1 << "::. " << m_num[0] << std::endl;
}

void modern_handle::make_handle(volatile class modern_handle& diff) volatile
{
	if (m_object)
	{
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
	if (m_object==nullptr)
		return;
	if (m_num[0] <= 1)
	{
		if (m_object[0])
			delete[] m_object;
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

volatile struct modern_class* const modern_handle::get()
{
	if (m_object)
		return m_object[0];
	else return nullptr;
}

void modern_handle::release()
{
	if (m_object == nullptr)
		return;
	if (m_num[0] <= 1)
	{
		if (m_object[0])
			delete[] m_object;
		m_object[0] = nullptr;
		m_num[0] = 0;
		delete m_num;
		delete m_object;
	}
	else
	{
		m_num[0]--;
	}
	m_num = nullptr;
	m_object = nullptr;
}

bool operator<(const modern_handle& lhs, const modern_handle& rhs)
{
	return lhs.m_object[0] < rhs.m_object[0];
}
