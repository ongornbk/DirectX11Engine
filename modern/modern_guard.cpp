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

//#define MODERN_GUARD_YIELD_WHEN_LOCKED
#ifdef MODERN_GUARD_YIELD_WHEN_LOCKED
#define MODERN_GUARD_YIELD _Thrd_yield();
#else
#define MODERN_GUARD_YIELD
#endif // YIELD_WHEN_LOCKED

modern_guard::modern_guard(struct modern_class* const object) modern_except_state
#ifdef MODERN_GUARDING_ENABLED
	: m_lock(&(object->m_lock))
#endif // MODERN_GUARDING_ENABLED
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		MODERN_GUARD_YIELD

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
#endif // MODERN_GUARDING_ENABLED
}

modern_guard::modern_guard(volatile struct modern_class* const object) modern_except_state
#ifdef MODERN_GUARDING_ENABLED
	: m_lock(&(object->m_lock))
#endif // MODERN_GUARDING_ENABLED
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		MODERN_GUARD_YIELD

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
#endif // MODERN_GUARDING_ENABLED
}

modern_guard::modern_guard(const struct modern_class* const object) modern_except_state
#ifdef MODERN_GUARDING_ENABLED
	: m_lock(&(object->m_lock))
#endif // MODERN_GUARDING_ENABLED
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		MODERN_GUARD_YIELD

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
#endif // MODERN_GUARDING_ENABLED
}

modern_guard::modern_guard(struct std::atomic<uint64_t>& lock) modern_except_state
#ifdef MODERN_GUARDING_ENABLED
	: m_lock(&lock)
#endif // MODERN_GUARDING_ENABLED
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_LOCKED, std::memory_order::memory_order_acquire) != modern_guard_status::GUARD_STATUS_FREE)
	{
		MODERN_GUARD_THROW
		MODERN_GUARD_YIELD

	}
	MODERN_GUARD_CHECK_IF_LOCK_FREE
#endif // MODERN_GUARDING_ENABLED
}

modern_guard::~modern_guard() modern_except_state
{
#ifdef MODERN_GUARDING_ENABLED
	m_lock->exchange(modern_guard_status::GUARD_STATUS_FREE, std::memory_order::memory_order_release);
#endif // MODERN_GUARDING_ENABLED
}

