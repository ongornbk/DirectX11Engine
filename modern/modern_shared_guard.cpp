#include "modern_shared_guard.h"

modern_shared_guard::modern_shared_guard(modern_class* const object) modern_except_state : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
}

modern_shared_guard::modern_shared_guard(volatile modern_class* const object) modern_except_state : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
}

modern_shared_guard::modern_shared_guard(const modern_class* const object) modern_except_state : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
}

modern_shared_guard::modern_shared_guard(std::atomic<int64_t>& lock) modern_except_state
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
}

modern_shared_guard::~modern_shared_guard() modern_except_state
{
	m_lock->exchange(modern_guard_status::GUARD_STATUS_FREE, std::memory_order::memory_order_release);
}
