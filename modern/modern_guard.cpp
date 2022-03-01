#include "modern_guard.h"
#include <iostream>

//#define MODERN_GUARD_THROW_WHEN_LOCKED
#ifdef MODERN_GUARD_THROW_WHEN_LOCKED
#define MODERN_GUARD_THROW throw std::exception();
#else
#define MODERN_GUARD_THROW
#endif // THROW_WHEN_LOCKED

//#define MODERN_GUARD_THROW_WHEN_NOT_LOCK_FREE
#ifdef MODERN_GUARD_THROW_WHEN_NOT_LOCK_FREE
#define MODERN_GUARD_CHECK_IF_LOCK_FREE if (!m_lock->is_lock_free()) throw std::exception();
#else
#define MODERN_GUARD_CHECK_IF_LOCK_FREE
#endif // MODERN_GUARD_THROW_WHEN_NOT_LOCK_FREE



modern_guard::modern_guard(struct modern_class* const object) noexcept : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		std::this_thread::yield();

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
}

modern_guard::modern_guard(volatile struct modern_class* const object) noexcept : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		std::this_thread::yield();

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
}

modern_guard::modern_guard(const struct modern_class* const object) noexcept : m_lock(&(object->m_lock))
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		std::this_thread::yield();

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
}

modern_guard::modern_guard(struct std::atomic<int64_t>& lock) noexcept : m_lock(&lock)
{
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		std::this_thread::yield();

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
}

modern_guard::~modern_guard() noexcept
{
	m_lock->exchange(modern_guard_status::GUARD_STATUS_FREE, std::memory_order::memory_order_release);
}

volatile class modern_guard& modern_guard_anonymous(modern_class* const object) noexcept
{
	return *(new volatile class modern_guard(object));
}
