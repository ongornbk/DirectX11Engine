#include "MPManager.h"
#include <iostream>

extern "C"
{
	static class MPManager* g_mpManager = nullptr;

	static void _stdcall smpl(void)
	{
#ifdef MODERN_MQUEUE_LOCK_ATOMIC
		class modern_mqueue_handle handle = g_mpManager->m_queue->obtain();
		class ITask* const task = (class ITask* const)handle.front();
		if (task)
		{
			task->execute();
			delete task;
			handle.pop();
		}
#else 
		class modern_mqueue_handle handle = g_mpManager->m_queue->obtain();
		class ITask* const task = (class ITask* const)handle.pop();
		if (task)
		{
			task->execute();
			delete task;
			//handle.pop();
		}
#endif MODERN_MQUEUE_LOCK_ATOMIC
	}
}

MPManager::MPManager(const size_t num_of_threads) : m_tempHandle(nullptr)
{
	m_pool = new modern_thread_pool(num_of_threads, smpl);
	m_queue = new modern_mqueue();
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
	if (m_queue)
	{
		delete m_queue;
		m_queue = nullptr;
	}
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

void MPManager::begin_weak_pushing()
{
	m_tempHandle = g_mpManager->m_queue->obtain_pointer();
	assert(m_tempHandle);
}

void MPManager::weak_push(ITask* const task)
{
	m_tempHandle->push(task);
}

void MPManager::push(ITask* const task)
{
	class modern_mqueue_handle handle = g_mpManager->m_queue->obtain();
	handle.push(task);
}

void MPManager::barrier()
{
	m_queue->barrier();
}

void MPManager::finalize_weak_pushing()
{
	delete m_tempHandle;
	m_tempHandle = nullptr;
}

void MPManager::increment()
{
	m_pool->inc();
}

void MPManager::decrement()
{
	m_pool->dec();
}
