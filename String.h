#pragma once
#include "Vector.h"

template <class T = char>
class String
{
	Vector<T> m_data;

public:

	u32 size()
	{
		m_data.size();
	}

	u32 capacity()
	{
		m_data.capacity();
	}

	T begin()
	{
		m_data.begin();
	}

	T end()
	{
		m_data.end();
	}

	T clear()
	{
		m_data.clear();
	}
};

#define String String<> 