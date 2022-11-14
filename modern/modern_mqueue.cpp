#pragma once
#include "modern_mqueue.h"
#include <mutex>

/*
Copyright(C) < 08.10.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

modern_mqueue::modern_mqueue() : m_queue{}
{
}

modern_mqueue::~modern_mqueue()
{

}

class modern_mqueue_handle&& modern_mqueue::obtain()
{
	return std::move(modern_mqueue_handle(this));
}

class modern_mqueue_handle* const modern_mqueue::obtain_pointer()
{
	return new modern_mqueue_handle(this);
}

void* const modern_mqueue::front() const modern_except_state
{
#ifdef MODERN_MQUEUE_LOCK_MUTEX
	std::unique_lock<std::mutex> m_lck(m_mtx);
	m_cv.wait(m_lck);
#endif // MODERN_MQUEUE_LOCK_MUTEX
	return m_queue.front();
}

void* const modern_mqueue::pop()
{
#ifdef MODERN_MQUEUE_LOCK_ATOMIC
	m_queueSize--;
	m_size.fetch_sub(1l);
#else
	m_size.fetch_sub(1l);
	std::unique_lock<std::mutex> m_lck(m_mtx);
	m_cv.wait(m_lck);
#endif // MODERN_MQUEUE_LOCK_ATOMIC

	//m_cv.wait();
	return m_queue.pop();
}

void modern_mqueue::push(void* const element)
{
#ifdef MODERN_MQUEUE_LOCK_ATOMIC
	m_size.fetch_add(1l);
	m_queueSize++;
#else
	m_size.fetch_add(1l);
	std::unique_lock<std::mutex> m_lck(m_mtx);
#endif // MODERN_MQUEUE_LOCK_ATOMIC

	m_queue.push(element);

#ifdef MODERN_MQUEUE_LOCK_MUTEX
	m_lck.unlock();
	m_cv.notify_one();
#endif // MODERN_MQUEUE_LOCK_MUTEX

}

const modern_Boolean modern_mqueue::consume(modern_task*& item)
{
	modern_guard g(this);

	if (m_queueSize.load() == 0ull) {
		return modern_false;
	}

	item = reinterpret_cast<modern_task*>(m_queue.front());
	m_queue.pop();
	m_queueSize--;
	return modern_true;
}

void modern_mqueue::produce(modern_task*&& item)
{
	modern_guard g(this);
	m_queue.push(item);
	m_queueSize++;
}

void modern_mqueue::barrier() const modern_thread_safe modern_except_state
{

//#ifdef MODERN_MQUEUE_LOCK_ATOMIC
//	while (m_size.load(std::memory_order::memory_order_seq_cst) > 0l)
//	{
//		_Thrd_yield();
//	}
//#else
//	//m_cv.wait(m_mtx);
//	//m_cv.wait
//	while (m_size.load(std::memory_order::memory_order_relaxed) > 0l)
//	{
//		_Thrd_yield();
//	}
//#endif // MODERN_MQUEUE_LOCK_ATOMIC

	while (m_queueSize.load())
	{

	}
}
