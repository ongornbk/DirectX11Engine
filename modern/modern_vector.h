#pragma once
#include "modern_memory.h"

template <class T>
class modern_vector
{
	T* m_data;
	size_t m_size;
	size_t m_capacity;
public:
	explicit modern_vector()
	{
		m_size = 0u;
		m_capacity = 4u * sizeof(T);
		m_data = mmalloc<T>(m_capacity);
		assert(m_data);
	}

	modern_vector(const size_t capacity)
	{
		assert(capacity);
		m_size = 0u;
		m_capacity = capacity;
		m_data = mmalloc<T>(m_capacity);
		assert(m_data);
	}

	~modern_vector()
	{
		for (size_t i = 0u;i<m_size;i++)
		{
			m_data[i].~T();
		}
		mfree(m_data);
	}

	void clear()
	{
		for (size_t i = 0u; i < m_size; i++)
		{
			m_data[i].~T();
		}
		m_size = 0;
	}

	void push_back(T element)
	{
		new (m_data + m_size) T(element);
		m_size++;
		if (m_size >= m_capacity)
		{
			m_capacity *= 2u;
			m_data = mrealloc<T>(m_data, m_capacity);
			assert(m_data);
		}
	}

	void push_backr(T& element)
	{
		new (m_data + m_size) T(element);
		m_size++;
		if (m_size >= m_capacity)
		{
			m_capacity *= 2u;
			m_data = mrealloc<T>(m_data, m_capacity);
			assert(m_data);
		}
	}

	T& operator[](const size_t element) const
	{
		assert(element < m_size);
		return m_data[element];
	}

	T& at(const size_t element) const
	{
		assert(element < m_size);
		return m_data[element];
	}

	T* begin() const modern_except_state
	{
		return m_data;
	}
	T* end() const modern_except_state
	{
		return m_data + m_size;
	}

	T*& data()
	{
		return m_data;
	}

	const size_t size() const
	{
		return m_size;
	}

	const size_t capacity() const
	{
		return m_capacity;
	}

	const bool empty() const
	{
		if (m_size) return false;
		else return true;
	}

	void reverse()
	{
		for (size_t i = 0u; i < m_size / 2u; i++)
			std::swap(m_data[i], m_data[m_size - i - 1]);
	}

	void pop_end()
	{
		if (m_size)
		{
			m_data[m_size].~T();
			m_size--;
		}
	}

};