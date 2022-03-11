#pragma once
#include "modern_def.h"

/*
Copyright(C) < 02.06.2020 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

template <class T>
class modern_weak;

template <class T>
class modern_shared
{
	T* m_pointer;
	int32_t* m_numOfCopies;

public:

	friend class modern_weak<T>;
	friend class modern_shared_view;

	explicit modern_shared(void)
	{ 
		m_pointer = nullptr;
		m_numOfCopies = nullptr; 
	}

	explicit constexpr modern_shared(T* const pointer) : m_pointer(pointer),m_numOfCopies(new int32_t())
	{
		(*m_numOfCopies) = 1;
		std::cout << "fdfdfdfdf";
	}

	~modern_shared() 
	{ 
		if (m_numOfCopies)
			if ((*m_numOfCopies) > 1)
			{
				(*m_numOfCopies)--;
			}
			else
			{ 
				delete m_pointer;
				m_pointer = nullptr;
				delete m_numOfCopies;
				m_numOfCopies = nullptr;
			}

	}

	modern_shared(modern_shared&) = delete;

	void make_shared(T* const pointer)
	{ 
		if (m_numOfCopies)
			switch (*m_numOfCopies)
			{
			case 1:
				delete m_numOfCopies;
				m_numOfCopies = nullptr;
				delete m_pointer;
				m_pointer = nullptr;
				break;
			default:
				(*m_numOfCopies)--;
			}
		m_pointer = pointer;
		m_numOfCopies = new int32_t();
		(*m_numOfCopies) = 1;


	}

	void make_shared(modern_shared<T>& shared)
	{
		if (!shared.m_numOfCopies)
			return;

		if(m_numOfCopies)
		switch (*m_numOfCopies)
		{
		case 1:
			delete m_numOfCopies;
			m_numOfCopies = nullptr;
			delete m_pointer;
			m_pointer = nullptr;
			break;
		default:
			(*m_numOfCopies)--;
		}
		assert(shared.m_numOfCopies);
		assert(shared.m_pointer);
		m_pointer = shared.m_pointer;
		m_numOfCopies = shared.m_numOfCopies;
		if(m_numOfCopies)
		(*m_numOfCopies)++;


	}

	[[nodiscard]] modern_shared<T>& return_shared(T* const pointer)
	{
		assert(pointer);
		m_pointer = pointer;
		m_numOfCopies = new int32_t();
		(*m_numOfCopies) = 0;
		return *this;
	}

	T& operator*() const noexcept {  assert(m_pointer); return *m_pointer; }
	T* operator->() const noexcept { assert(m_pointer); return m_pointer; }
	T& operator= (const T& shared)
	{
		if (this == &shared)
			return *this;


		m_pointer = shared.m_pointer;
		m_numOfCopies = shared.m_numOfCopies;
		(*m_numOfCopies)++;

		return *this;
	}

	const int32_t getNumberOfCopies() const noexcept
	{ 
		if (m_numOfCopies)
			return (*m_numOfCopies);
		else return -1;
	}

	const bool isInitialized() const noexcept
	{
		if (m_pointer) return true;
		else return false;
	}
};