/*
Copyright(C) < 02.06.2020 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

#pragma once
#include "modern_def.h"
#include "modern_memory.h"

//#define MODERN_ARRAY_DEBUG
#ifdef MODERN_ARRAY_DEBUG
#define modern_array_assert(condition) assert(condition)
#else
#define modern_array_assert(condition)
#endif MODERN_ARRAY_DEBUG

template <class T>
class modern_array
{
	T* m_data;
	size_t m_size;
	size_t m_capacity;

public:

	explicit modern_array()
		{
		m_size = 0ull;
		m_capacity = 4ull;
		m_data = mmalloc<T>(m_capacity);
		modern_array_assert(m_data);
		}

	modern_array(const size_t capacity)
	{
		modern_array_assert(capacity);
		m_size = 0ull;
		m_capacity = capacity;
		m_data = mmalloc<T>(m_capacity);
		modern_array_assert(m_data);
	}

	modern_array(const size_t size,void* const)
	{
		this->initialize(size, nullptr);
	}

	~modern_array()
	{
		mfree(m_data);
	}

	T* begin() const modern_except_state
	{
		return m_data;
	}
	T* end() const modern_except_state
	{
		return (m_data + m_size);
	}

	T& operator[](const size_t element) const
	{
		modern_array_assert(element < m_size);
		return *(m_data + element);
	}

	T& at(const size_t element) const
	{
		modern_array_assert(element < m_size);
		return *(m_data + element);
	}

	void resize(const size_t size = m_capacity)
	{
		modern_array_assert(size > 0ull);
		m_size = size;
		if (m_size > m_capacity)
		{
			m_capacity = m_size;
			m_data = mrealloc<T>(m_data,m_capacity);
			modern_array_assert(m_data);
		}
	}

	void expand_size(const size_t size)
	{
		modern_array_assert(size);
		m_size += size;
		if (m_size > m_capacity)
		{
			m_capacity = m_size;
			m_data = mrealloc<T>(m_data, m_capacity);
			modern_array_assert(m_data);
		}
	}

	void reserve(const size_t capacity)
	{
		modern_array_assert(capacity > 0ull);
		if (capacity > m_capacity)
		{
			m_capacity = capacity;
			m_data = mrealloc<T>(m_data, m_capacity);
			modern_array_assert(m_data);
		}
	}

	void push_back(T element)
	{
		m_data[m_size] = element;
		m_size++;
		if (m_size >= m_capacity)
		{
			m_capacity *= 2ull;
			m_data = mrealloc<T>(m_data, m_capacity);
			modern_array_assert(m_data);
		}
		
	}

	void copy_back(T* collection,const size_t size)
	{
		modern_array_assert(size);
		modern_array_assert(collection);
		for (size_t i = 0ull; i < size; i++)
		{
			push_back(collection[i]);
		}
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

	void clear()
	{
		m_size = 0ull;
	}

	void shrink()
	{
		if (m_capacity > m_size + 1ull)
		{
			m_capacity = m_size + 1ull;
			m_data = mrealloc<T>(m_data,m_capacity);
		}
	}

	void reverse()
	{
		for (size_t i = 0ull; i < m_size / 2ull; i++)
			std::swap(m_data[i], m_data[m_size - i - 1ull]);
	}

	void remove(const size_t index)
	{
		modern_array_assert(index >= 0ull && index < m_size);
		if (index > m_size || m_size < 1ull)
			return;
		for (size_t i = index; i < m_size; ++i)
			m_data[i] = m_data[i + 1ull];
		m_size--;
	}

	void initialize(const size_t size,void* const)
	{
		modern_array_assert(size);
		m_size = size;
		m_capacity = size + 1ull;
		m_data = mcalloc<T>(m_capacity);
		modern_array_assert(m_data);
	}
};
