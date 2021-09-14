#pragma once
#include "ITrash.h"
#include "gdef.h"
#include <queue>
#include <deque>
#include "modern/modern_array.h"

class GarbageCollector
{
	std::deque<class ITrash> m_garbage;

public:

	void AsyncDelete(void* ptr);

	template <class T>
	void AsyncDeleteArray(modern_array<T>* __array);

	void AsyncFree(void* ptr);

	void Update();

	static GarbageCollector* GetInstance() noexcept;
};

#include "GarbageCollector.inl"

