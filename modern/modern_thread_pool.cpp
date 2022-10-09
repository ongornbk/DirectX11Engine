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
	unsigned int _stdcall slave_loop(void*)
	{
		class modern_thread_pool* const m_pool = s_pool;
		
		if (m_pool)
		{

			void(__stdcall* const m_loop)(void) = reinterpret_cast<void(__stdcall* const)(void)>(m_pool->getLoop());
		repeat:
			const enum class modern_thread_pool_state state = m_pool->state();
			switch (state)
			{
			case modern_thread_pool_state::MODERN_THREAD_POOL_STATE_RUNNING:
			{
				m_loop();
				goto repeat;
			}
			case modern_thread_pool_state::MODERN_THREAD_POOL_STATE_DECREMENT:
			{
				if (_Thrd_id() == m_pool->get_dec())
				{
					break;
				}
				else
				{
					goto repeat;
				}
			}
			case modern_thread_pool_state::MODERN_THREAD_POOL_STATE_STOPPED:
			{
				break;
			}
			}
		}
		return 0ul;
	}
}

modern_thread_pool::modern_thread_pool(const size_t num_of_threads, void(__stdcall* const loop)(void))
	{
		s_pool = this;
		m_loop = loop;
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
		m_state.store(modern_thread_pool_state::MODERN_THREAD_POOL_STATE_RUNNING, std::memory_order::memory_order_seq_cst);
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

	void modern_thread_pool::dec()
	{
		if (m_threads.size() > 1ull)
		{
			m_dec_thrd_id = m_threads.end()->get_id();
			m_state.store(modern_thread_pool_state::MODERN_THREAD_POOL_STATE_DECREMENT, std::memory_order::memory_order_seq_cst);
			if (m_dec_thrd_id)
			{
				m_threads.end()->join();
			}
			m_threads.pop_end();
		}
	}

	void modern_thread_pool::inc()
	{
		//resize vector
		//m_threads.push_back(* new modern_thread(slave_loop));
		//m_threads.end()->start();
	}

	void* const modern_thread_pool::getLoop()
	{
		return m_loop;
	}

	const unsigned int modern_thread_pool::get_dec() const modern_thread_safe modern_except_state
	{
		return m_dec_thrd_id;
	}