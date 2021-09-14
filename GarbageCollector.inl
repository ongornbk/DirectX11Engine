#pragma once
#include "DeleteArrayTrash.h"

template<class T>
inline void GarbageCollector::AsyncDeleteArray(modern_array<T>* __array)
{
	m_garbage.push_back(DeleteArrayTrash<T>(__array));
}
