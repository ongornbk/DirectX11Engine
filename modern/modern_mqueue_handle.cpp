#include "modern_mqueue_handle.h"
#include "modern_mqueue.h"


/*
Copyright(C) < 08.10.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

modern_mqueue_handle::modern_mqueue_handle(class modern_mqueue* const queue)
#ifdef MODERN_MQUEUE_LOCK_ATOMIC
	: 
modern_guard((struct modern_class* const)queue), m_queue(queue)//, m_size(0ll)
#else
	:
m_queue(queue)
#endif // MODERN_MQUEUE_LOCK_ATOMIC
	{
	//m_state.store(modern_true, std::memory_order_seq_cst);
	}

modern_mqueue_handle::modern_mqueue_handle(class modern_mqueue_handle&& handle) modern_except_state
#ifdef MODERN_MQUEUE_LOCK_ATOMIC
	:
		m_queue(std::move(handle.m_queue)),
		modern_guard(std::move((struct modern_class* const)handle.m_queue))
#else
	:
	m_queue(std::move(handle.m_queue))
#endif // MODERN_MQUEUE_LOCK_ATOMIC
{

}

modern_mqueue_handle::~modern_mqueue_handle()
	{

	}

	void* const modern_mqueue_handle::front() const modern_except_state
	{
		return m_queue->front();
	}

	void* const modern_mqueue_handle::pop()
	{
		//m_size--;
		//if (m_size == 0)
		//{
		////	m_state.store(modern_false, std::memory_order::memory_order_seq_cst);
		//}
		return m_queue->pop();
	}

	void modern_mqueue_handle::push(void* const element)
	{
		//m_size++;
		m_queue->push(element);
	}
