#include "modern_thread_pool.h"

/*
Copyright(C) < 08.10.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

	static class modern_thread_pool* s_pool{};


extern "C"
{
	static unsigned int _stdcall slave_loop(void*)
	{
		class modern_thread_pool* m_pool = s_pool;
		while (m_pool->state() == modern_thread_pool_state::MODERN_THREAD_POOL_STATE_RUNNING)
		{

		}
		return 0ul;
	}
}

modern_thread_pool::modern_thread_pool(const size_t num_of_threads)
	{
		s_pool = this;
		for (size_t i = 0ull; i < num_of_threads; ++i)
		{
			m_threads.push_back(modern_thread(slave_loop));
		}
	}

modern_thread_pool::~modern_thread_pool()
	{
		m_threads.clear();
	}

	const enum class modern_thread_pool_state modern_thread_pool::state() const modern_except_state
	{
		return m_state.load(std::memory_order::memory_order_acquire);
	}

	void modern_thread_pool::start()
	{
		for (size_t i = 0ull; i < m_threads.size(); ++i)
		{
			m_threads[i].start();
		}
	}

	void modern_thread_pool::join()
	{
		m_state.store(modern_thread_pool_state::MODERN_THREAD_POOL_STATE_STOPPED, std::memory_order::memory_order_seq_cst);
		for (size_t i = 0ull; i < m_threads.size(); ++i)
		{
			m_threads[i].join();
		}
	}
