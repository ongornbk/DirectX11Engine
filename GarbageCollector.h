#pragma once
#include "ITrash.h"
#include "gdef.h"
#include <queue>
#include <deque>
#include "modern/modern_array.h"
#include "RenderContainer.h"

class GarbageCollector
{
	std::deque<class ITrash> m_garbage;
	//std::deque<class modern_handle> m_handles;

public:

	void AsyncDelete(void* ptr);
	void AsyncDelete(class EObject* const obj);

	template <class T>
	void AsyncDeleteArray(modern_array<T>* __array);

	void AsyncFree(void* ptr);

	void Update();

	static GarbageCollector* GetInstance() noexcept;
};

#include "GarbageCollector.inl"

