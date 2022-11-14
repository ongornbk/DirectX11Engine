#pragma once
#include "modern_def.h"
#include "modern_memory.h"
#include "modern_queue.h"
#include "modern_task.h"
#include "modern_mqueue_handle.h"
#include "modern_condition_variable.h"

/*
Copyright(C) < 08.10.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/



class modern_mqueue_handle;



class modern_mqueue
#ifdef MODERN_MQUEUE_LOCK_ATOMIC
	: modern_class
#endif // MODERN_MQUEUE_LOCK_ATOMIC
{
	class modern_queue m_queue;
//volatile size_t m_queueSize = 0ull;
#ifdef MODERN_MQUEUE_LOCK_MUTEX
mutable modern_condition_variable m_cv;
mutable std::mutex m_mtx;
mutable std::atomic<int32_t> m_queueSize;
#endif // MODERN_MQUEUE_LOCK_MUTEX
mutable std::atomic<size_t> m_queueSize;
public:

	modern_mqueue();

	~modern_mqueue();

	class modern_mqueue_handle* const modern_mqueue::obtain_pointer();
	[[nodiscard]]class modern_mqueue_handle&& obtain();//nodiscard!
	const modern_Boolean consume(modern_task*& const item);
	void produce(modern_task*&& item);

#ifdef MODERN_MQUEUE_LOCK_ATOMIC
	mutable std::atomic<int32_t> m_size;
#endif // MODERN_MQUEUE_LOCK_ATOMIC

private:

	friend class modern_mqueue_handle;

	void* const front() const modern_except_state;
	
	void* const pop();
	
	void push(void* const element);



public:

	 void barrier() const modern_thread_safe modern_except_state;
};

typedef class modern_mqueue_handle& modern_mqueue_handle_ref;