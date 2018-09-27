#pragma once
#include <cstdint>

class ThreadManager
{
public:
	~ThreadManager();
	static void InitializeThreadManager(uint8_t numThreads = 1u);

	friend struct mThread;

	ThreadManager();
	void Initialize(uint8_t numThreads);

	uint8_t m_runningThreads;
};

