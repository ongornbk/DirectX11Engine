#include "ThreadManager.h"
#include <atomic>
#include <mutex>
#include <future>
#include <thread>

struct mThread
{
#define UNINITIALIZED 0U
#define CLOSED        1U

	mThread()
	{
		state = UNINITIALIZED;
	}

	void Close()
	{
		state = CLOSED;
	}

	std::atomic<int32_t> state;
	std::thread thread;
};

namespace
{
	std::shared_ptr<ThreadManager> m_instance = nullptr;
	std::shared_ptr<std::vector<std::unique_ptr<mThread>>> m_threads = nullptr;
}

ThreadManager::ThreadManager()
{
}

void ThreadManager::Initialize(uint8_t numThreads)
{
	m_runningThreads = numThreads;
	m_threads = std::make_shared<std::vector<std::unique_ptr<mThread>>>();
	m_threads.get()->reserve(m_runningThreads);
}


ThreadManager::~ThreadManager()
{
	for (auto && thread : *(m_threads.get()))
	{
		if (thread.get())
		{
			thread.get()->Close();
		}
	}
	m_threads.get()->clear();
}

void ThreadManager::InitializeThreadManager(uint8_t numThreads)
{
	m_instance = std::make_shared<ThreadManager>();
	m_instance.get()->Initialize(numThreads);
}
