#pragma once
#include "gdef.h"

template <class T>
class Vector
{
public:

	explicit Vector()
	{
		m_size = 0u;
		m_capacity = 2u;
		m_data = (T*)malloc(sizeof(T)*m_capacity);
	}
	Vector(u32 capacity)
	{
		m_size = 0u;
		m_capacity = capacity;
		m_data = (T*)malloc(sizeof(T)*m_capacity);
	}
	~Vector()
	{
		free(m_data);
	}

	T* begin()
	{
		return m_data;
	}
	T* end()
	{
		return (m_data + m_size);
	}
	T& operator[](u32 element)
	{
		return *(m_data + element);
	}

	void resize(u32 size = m_capacity)
	{
		m_size = size;
		if (m_size > m_capacity)
		{
			m_capacity = m_size;
			m_data = (T*)realloc(m_data, sizeof(T)*m_capacity);
		}
	}

	void push_back(const T  element)
	{
		m_size++;
		if (m_size >= m_capacity)
		{
			m_capacity *= 2u;
			m_data = (T*)realloc(m_data, sizeof(T)*m_capacity);
		}
		m_data[m_size - 1u] = element;
	}

	T* data() const 
	{
		return m_data;
	}

	const u32 size() const
	{
		return m_size;
	}

	const u32 capacity() const 
	{
		return m_capacity;
	}

	const bool empty() const
	{
		if (m_size) return false;
		else return true;
	}

	void clear()
	{
		//free(m_data);
		m_size = 0u;
		//m_capacity = 2u;
		//m_data = (T*)malloc(sizeof(T)*m_capacity);
	}

private:

	T* m_data;
	u32 m_capacity;
	u32 m_size;

};

