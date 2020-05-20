#pragma once
#include "ITrash.h"
#include "gdef.h"
#include <queue>
#include <deque>

class GarbageCollector
{
	std::deque<class ITrash> m_garbage;

public:

	void AsyncDelete(void* ptr);

	void AsyncFree(void* ptr);

	void Update();

	static GarbageCollector* GetInstance() noexcept;
};

