/*
Copyright(C) < 06.12.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

#pragma once
#include "modern_def.h"
#include "modern_memory.h"

enum class modern_barray_stance
{
	ENUM_MODERN_BARRAY_STANCE_FORWARD,
	ENUM_MODERN_BARRAY_STANCE_BACKWARD,
	COUNT
};

template <class T>
class modern_barray
{
	T* m_data;
	union
	{
		struct
		{
			size_t m_sizeA;
			size_t m_sizeB;
		};
		size_t m_size[enum_cast<size_t>(modern_barray_stance::COUNT)];
	}
	size_t m_capacity;

	enum class modern_barray_stance m_stance = modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_FORWARD;

public:

	explicit modern_array()
		{
		m_sizeA = 0ull;
		m_sizeB = 0ull;
		m_capacity = 4ull;
		m_data = mmalloc<T>(m_capacity);
		assert(m_data);
		}

	modern_array(const size_t capacity)
	{
		assert(capacity);
		m_sizeA = 0ull;
		m_sizeB = 0ull;
		m_capacity = capacity;
		m_data = mmalloc<T>(m_capacity);
		assert(m_data);
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
		switch (m_stance)
		{
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_FORWARD:
		{
			return m_data;
		}
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_BACKWARD:
		{
			return (m_data + m_capacity - m_sizeB);
		}
		}
		return nullptr;
	}
	T* end() const modern_except_state
	{
		
		switch (m_stance)
		{
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_FORWARD:
		{
			return (m_data + m_sizeA);
		}
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_BACKWARD:
		{
			return (m_data + m_capacity);
		}
		}
		return nullptr;
	}

	T& operator[](const size_t element) const
	{

		switch (m_stance)
		{
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_FORWARD:
		{
			assert(element < m_sizeA);
			return *(m_data + element);
		}
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_BACKWARD:
		{
			assert(element < m_sizeB);
			return *(m_data + m_capacity - element);
		}
		}
		//return nullptr;
	}

	T& at(const size_t element) const
	{
		switch (m_stance)
		{
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_FORWARD:
		{
			assert(element < m_sizeA);
			return *(m_data + element);
		}
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_BACKWARD:
		{
			assert(element < m_sizeB);
			return *(m_data + m_capacity - element);
		}
		}
		//return nullptr;
	}

	void resize(const size_t size = m_capacity)
	{
		assert(size > 0ull);
		m_size[enum_cast<size_t>(m_stance)] = size;

		if ((m_sizeA + m_sizeB) > m_capacity)
		{
			m_capacity = m_sizeA + m_sizeB;
			m_data = mrealloc<T>(m_data,m_capacity);
			assert(m_data);
		}
	}

	void expand_size(const size_t size)
	{
		assert(size);
		m_size[enum_cast<size_t>(m_stance)] += size;
		if ((m_sizeA + m_sizeB) > m_capacity)
		{
			m_capacity = m_sizeA + m_sizeB;
			m_data = mrealloc<T>(m_data, m_capacity);
			assert(m_data);
		}
	}

	void reserve(const size_t capacity)
	{
		assert(capacity > 0ull);
		if (capacity > m_capacity)
		{
			m_capacity = capacity;
			m_data = mrealloc<T>(m_data, m_capacity);
			assert(m_data);
		}
	}

	void push_back(T element)
	{
		switch (m_stance)
		{
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_FORWARD:
		{
			m_data[m_size] = element;
			m_sizeA++;
			break;
		}
		case modern_barray_stance::ENUM_MODERN_BARRAY_STANCE_BACKWARD:
		{
			m_data[m_capacity - m_sizeB] = element;
			m_sizeB++;
			break;
		}
		}

		if (m_size >= m_capacity)
		{
			m_capacity *= 2ull;
			m_data = mrealloc<T>(m_data, m_capacity);
			assert(m_data);	
		}
		
	}

	void copy_back(T* collection,const size_t size)
	{
		assert(size);
		assert(collection);


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
		return m_size[enum_cast<size_t>(m_stance)];
	}

	const size_t capacity() const
	{
		return m_capacity;
	}

	const bool empty() const
	{
		if (m_size[enum_cast<size_t>(m_stance)]) return false;
		else return true;
	}

	void clear()
	{
		m_size[enum_cast<size_t>(m_stance)] = 0ull;
	}

	void shrink()
	{
		if (m_capacity > m_sizeA + m_sizeB + 1ull)
		{
			m_capacity = m_sizeA + m_sizeB + 1ull;
			m_data = mrealloc<T>(m_data,m_capacity);
		}
	}

	void reverse()
	{
		//for (size_t i = 0ull; i < m_size / 2ull; i++)
		//	std::swap(m_data[i], m_data[m_size - i - 1ull]);
	}

	void remove(const int32_t index)
	{
		//assert(index >= 0 && index < m_size);
		//if (index > m_size || m_size < 1)
		//	return;
		//for (int32_t i = index; i < m_size; ++i)
		//	m_data[i] = m_data[i + 1];
		//m_size--;
	}

	void initialize(const size_t size,void* const)
	{
		assert(size);
		m_size = size;
		m_capacity = size;
		m_data = mcalloc<T>(size);
		assert(m_data);
	}
};
