#include "MPManager.h"
#include <iostream>

extern "C"
{
	static class MPManager* g_mpManager = nullptr;

	void _stdcall smpl(void)
	{
		//if(g_mpManager->m_queue.isEmpty())
		//return;
	 class modern_task** task{};
		//;

				//if (task)
				//{
				//	task->execute();
				//	delete task;
				//}	
				////g_mpManager->m_queue.popFront();
				task = g_mpManager->m_queue.frontPtr();

			if (!task);
			return;

			if (task[0])
			{
				task[0]->execute();
				delete task[0];
			}
			g_mpManager->m_queue.popFront();
		
	}
}

MPManager::MPManager(const size_t num_of_threads) : m_queue(16ul)
{
	m_pool = new modern_thread_pool(num_of_threads, smpl);
	//m_queue = new modern_mqueue();
	m_pool->start();
}

MPManager::~MPManager()
{
	m_pool->join();
	if (m_pool)
	{
		delete m_pool;
		m_pool = nullptr;
	}
	//if (m_queue)
	//{
	//	delete m_queue;
	//	m_queue = nullptr;
	//}
}

void MPManager::Initialize(const size_t num_of_threads)
{
	g_mpManager = new class MPManager(num_of_threads);
}

void MPManager::Release()
{
	if (g_mpManager)
	{
		delete g_mpManager;
		g_mpManager = nullptr;
	}
	//throw;
}

class MPManager* const MPManager::Get()
{
	return g_mpManager;
}

void MPManager::push(class modern_task* task)
{
	task->execute();
	delete task;
	//m_queue.write(task);
	//while (!m_queue.write(task)) {
	//	//spin until the queue has room
	//	continue;
	//}
}

void MPManager::barrier()
{
	//m_queue->barrier();
	//while (m_queue.sizeGuess() - 1ull)
	//{
	//
	//}
	//while (!m_queue.isEmpty())
	//{
	//	g_mpManager->m_queue.popFront();
	//}
}

