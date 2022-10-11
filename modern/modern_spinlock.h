/*
Copyright(C) < 10.9.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

#pragma once
#include "modern_static_array.h"
#include "modern_task.h"
#include <atomic>
#include <condition_variable>

class modern_task_do_nothing : public modern_task
{
public:
	void execute() override
	{

	}
};

class modern_spinlock
{
	class modern_static_array<class modern_task*, 256ull> m_tasks;

	std::atomic<uint8_t> m_conP;
	std::atomic<uint8_t> m_proP;
	std::atomic<uint8_t> m_size;

	std::condition_variable m_cv;
	std::mutex              m_mtx;

	std::atomic_bool        m_ready{ modern_false };

	class modern_task_do_nothing m_dn;

public:
	modern_spinlock()
	{
		for (int i = 0; i < 256; i++)
		{
			m_tasks[i] = &m_dn;
		}
	}

	void push(class modern_task* const task)
	{
		while (m_size.load() >= 16u)
		{

		}
		{
			//std::lock_guard<std::mutex> lck(m_mtx);
			m_ready.store(modern_true);
		}
		m_tasks[m_proP.load()] = task;
		m_proP++;
		m_size++;
		
		m_cv.notify_one();
	}
	void consume()
	{
		while (m_size.load() == 0u)
		{

		}
		std::unique_lock<std::mutex> m_lock(m_mtx);
		m_cv.wait(m_lock, [this] { return m_ready.load(); });
		const uint8_t index = m_conP.load();
		class modern_task* const task = m_tasks[index];
		m_conP++;
		m_lock.unlock();
		m_size--;
		task->execute();
		//delete task;
	}
};