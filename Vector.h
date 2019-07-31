#pragma once
#include "gdef.h"

template <class T>
class Vector
{
public:

	explicit Vector()
	{
		m_size = 0;
		m_capacity = 2;
		m_data = (T*)malloc(sizeof(T)*m_capacity);
	}
	Vector(const int32 capacity)
	{
		m_size = 0;
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
	T& operator[](const int32 element)
	{
		return *(m_data + element);
	}

	T& at(const int32 element)
	{
		return *(m_data + element);
	}

	void resize(const int32 size = m_capacity)
	{
		m_size = size;
		if (m_size > m_capacity)
		{
			m_capacity = m_size;
			m_data = (T*)realloc(m_data, sizeof(T)*m_capacity);
		}
	}

	void reserve(const int32 capacity)
	{
		if (capacity > m_capacity)
		{
			m_data = (T*)realloc(m_data, sizeof(T)*capacity);
		}
	}

	void push_back(T element)
	{
		m_size++;
		if (m_size >= m_capacity)
		{
			m_capacity *= 2;
			m_data = (T*)realloc(m_data, sizeof(T)*m_capacity);
		}
		m_data[m_size - 1] = element;
	}

	

	T* data() 
	{
		return m_data;
	}

	const int32 size() const noexcept
	{
		return m_size;
	}

	const int32 capacity() const noexcept
	{
		return m_capacity;
	}

	const bool empty() const noexcept
	{
		if (m_size) return false;
		else return true;
	}

	void clear() noexcept
	{
		m_size = 0;
	}

	void remove(const int32 index)
	{
		if (index > m_size || m_size < 1)
			return;
		for (int32 i = index; i < m_size; ++i)
			m_data[i] = m_data[i + 1];
		m_size--;
	}

private:

	T* m_data;
	int32 m_capacity;
	int32 m_size;

};

template <class T>
class Vector_view
{
	T* m_data;
	int32 m_size;
public:

	explicit Vector_view(const T* data, const int32 size)
	{
		m_data = data;
		m_size = size;
	}

	explicit Vector_view(T* begin,T* end)
	{
		m_size = (int32)(end - begin);
		m_data = begin;
	}

	~Vector_view()
	{

	}
	T* begin()
	{
		return m_data;
	}
	T* end()
	{
		return (m_data + m_size);
	}
	T operator[](const int32 element) const
	{
		return *(m_data + element);
	}

	uint32 size() const noexcept
	{
		return m_size;
	}
};
