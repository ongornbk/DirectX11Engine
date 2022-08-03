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
	if ((&diff) && diff.m_object)
	{
		m_object = diff.m_object;
		m_num = diff.m_num;
		m_num[0]++;
	}
	else
	{
		m_num = nullptr;
		m_object = nullptr;
	}
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
			m_object = nullptr;
		}
		else
		{
			m_num[0]--;
		}
	}
	m_object = diff.m_object;
	m_num = diff.m_num;

	if (m_num)//case where diff is uninitialized
	{
		m_num[0]++;
	}
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
			m_object = nullptr;
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

	if (m_num)//case where diff is uninitialized
	{
		m_num[0]++;
	}

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
	if (m_num[0ll] <= 1ll)
	{
		if (m_object[0ll])
			delete[] m_object;
		m_object[0] = nullptr;
		m_num[0ll] = 0ll;
		delete m_num;
		delete m_object;
		m_num = nullptr;
		m_object = nullptr;
	//	std::cout << "delete handle" << std::endl;
	}
	else
	{
		m_num[0ll]--;
	//	std::cout << (m_num[0])+1 << "::. " << m_num[0] << std::endl;
	}
}

volatile modern_class* modern_handle::operator->()
{
	return m_object[0ll];
}

volatile struct modern_class* const modern_handle::get()
{
	if (m_object)
		return m_object[0ll];
	else return nullptr;
}

void modern_handle::release()
{
	if (m_object == nullptr)
		return;
	if (m_num[0ll] <= 1ll)
	{
		if (m_object[0ll])
			delete[] m_object;
		m_object[0] = nullptr;
		m_num[0ll] = 0ll;
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

bool operator<(const class modern_handle& lhs, const class modern_handle& rhs)
{
	return lhs.m_object[0] < rhs.m_object[0];
}

modern_weak_handle::modern_weak_handle()
{
	m_num = nullptr;
	m_object = nullptr;
}

modern_weak_handle::~modern_weak_handle()
{
}

modern_weak_handle::modern_weak_handle(const modern_handle& diff)
{
	if ((&diff) && diff.m_object)
	{
		m_object = diff.m_object;
		m_num = diff.m_num;
	}
	else
	{
		m_num = nullptr;
		m_object = nullptr;
	}
}

volatile modern_class* const modern_weak_handle::get()
{
	if (m_object)
		return m_object[0ll];
	else return nullptr;
}

void modern_weak_handle::make_weak_handle(const modern_handle& diff)
{
	if ((&diff) && diff.m_object)
	{
		m_object = diff.m_object;
		m_num = diff.m_num;
	}
	else
	{
		m_num = nullptr;
		m_object = nullptr;
	}
}

void modern_weak_handle::make_weak_handle(volatile modern_handle& diff) volatile
{
	if ((&diff) && diff.m_object)
	{
		m_object = diff.m_object;
		m_num = diff.m_num;
	}
	else
	{
		m_num = nullptr;
		m_object = nullptr;
	}
}

void modern_weak_handle::make_weak_handle(const modern_weak_handle& diff)
{
	if ((&diff) && diff.m_object)
	{
		m_object = diff.m_object;
		m_num = diff.m_num;
	}
	else
	{
		m_num = nullptr;
		m_object = nullptr;
	}
}

void modern_weak_handle::make_weak_handle(volatile modern_weak_handle& diff) volatile
{
	if ((&diff) && diff.m_object)
	{
		m_object = diff.m_object;
		m_num = diff.m_num;
	}
	else
	{
		m_num = nullptr;
		m_object = nullptr;
	}
}
