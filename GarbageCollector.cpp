#include "GarbageCollector.h"
#include "FreeTrash.h"
#include "DeleteTrash.h"
#include <mutex>

namespace
{
	static GarbageCollector* m_collector = nullptr;
}

void GarbageCollector::AsyncDelete(void* ptr)
{
	m_garbage.push_back(DeleteTrash(ptr));
}

void GarbageCollector::AsyncFree(void* ptr)
{

	m_garbage.push_back(FreeTrash(ptr));
}

void GarbageCollector::Update()
{
	m_garbage.clear();
}

GarbageCollector* GarbageCollector::GetInstance() noexcept
{
	if (m_collector)
		return m_collector;
	else return new GarbageCollector();
}
