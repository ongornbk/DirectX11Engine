/*
Copyright(C) < 10.9.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

#pragma once
#include "modern_def.h"
#include "modern_memory.h"

//#define MODERN_STATIC_ARRAY_DEBUG
#ifdef MODERN_STATIC_ARRAY_DEBUG
#define modern_static_array_assert(condition) assert(condition)
#else
#define modern_static_array_assert(condition)
#endif MODERN_STATIC_ARRAY_DEBUG

template <class T,size_t t_SIZE>
class modern_static_array
{
	T m_data[t_SIZE];
public:

	explicit modern_static_array()
		{

		}

	~modern_static_array()
	{

	}

	T& operator[](const size_t element)
	{
		return m_data[element];
	}

	T& at(const size_t element)
	{
		return m_data[element];
	}

	T*& data()
	{
		return &m_data;
	}

};
