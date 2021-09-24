#include "modern_guard.h"

modern_guard::modern_guard(modern_class* const object) noexcept : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		std::this_thread::yield();

	}
}

modern_guard::modern_guard(volatile modern_class* const object) noexcept : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		std::this_thread::yield();

	}
}

modern_guard::modern_guard(const modern_class* const object) noexcept : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		std::this_thread::yield();

	}
}

modern_guard::modern_guard(std::atomic<int64_t>& lock) noexcept : m_lock(&lock)
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		std::this_thread::yield();

	}
}

modern_guard::~modern_guard() noexcept
{
	m_lock->exchange(modern_guard_status::GUARD_STATUS_FREE, std::memory_order::memory_order_release);
}