#pragma once
#include "ITrash.h"
#include "gdef.h"
#include <deque>
#include "GameObject.h"

class GarbageCollector
{
	std::deque<class ITrash> m_garbage;
	//std::deque<class modern_handle> m_handles;

public:

	void AsyncDelete(void* ptr);
	void AsyncDelete(class GameObject* const obj);

	template <class T>
	void AsyncDeleteArray(modern_array<T>* __array);

	void AsyncFree(void* ptr);

	void Update();

	static GarbageCollector* GetInstance() modern_except_state;
};

#include "GarbageCollector.inl"

