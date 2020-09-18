#pragma once
#include "modern_def.h"
#include "modern_shared.h"

/*
Copyright(C) < 02.06.2020 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/


template <class T>
class modern_weak
{
	T* m_pointer;
	int32_t* m_numOfCopies;

public:
	explicit modern_weak(void)
	{
		m_pointer = nullptr;
		m_numOfCopies = nullptr;
	}

	~modern_weak()
	{

	}

	modern_weak(modern_weak&) = delete;

	void make_weak(modern_shared<T>& shared)
	{
		assert(shared.m_numOfCopies);
		assert(shared.m_pointer);
		m_pointer = shared.m_pointer;
		m_numOfCopies = shared.m_numOfCopies;
	}

	[[nodiscard]] modern_shared<T>& return_shared(T* const pointer)
	{
		assert(pointer);
		modern_shared<T>* shared = new modern_shared<T>();
		make_weak(shared->return_shared(pointer));
		return *shared;
	}

	T& operator*() const noexcept { assert(m_pointer); return *m_pointer; }
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