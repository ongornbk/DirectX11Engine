#include "modern_memory.h"
#include "modern_element.h"

/*
Copyright(C) < 03.15.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

class modern_queue
{
	struct modern_element* first;
	struct modern_element* last;

public:

	constexpr modern_queue() : first(nullptr),last(nullptr)
	{

		first = last = nullptr;
	}

	~modern_queue()
	{
		modern_element* next;
		while (first) {
			next = first->next;
			delete first;
			first = next;
		}
		first = nullptr;
		last = nullptr;
	}

	void* front() const noexcept
	{
		if (first)
			return first->data;
		return nullptr;
	}

	void* pop()
	{
		if (first)
		{
			void* dr = first->data;
			modern_element* temp = first;
			if (first == last) first = last = nullptr;
			else first = first->next;
			delete(temp);
			return dr;
		}
		return nullptr;
	}

	void push(void* element)
	{
		modern_element* n = new modern_element(nullptr,element);
		if (last == nullptr)
		{
			last = first = n;
		}
		else
		{
			last->next = n;
			last = n;
		}
	}
};