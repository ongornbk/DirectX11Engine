#pragma once
#include <queue>
class GarbageCollector
{
	std::queue<void*> m_garbage;

	void AsyncDelete(void* ptr);
};

