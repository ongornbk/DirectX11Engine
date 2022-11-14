#include "modern_shared_guard.h"

modern_shared_guard::modern_shared_guard(modern_class* const object) modern_except_state
#ifdef MODERN_GUARDING_ENABLED
	: m_lock(&(object->m_lock))
#endif MODERN_GUARDING_ENABLED
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
#endif MODERN_GUARDING_ENABLED
}

modern_shared_guard::modern_shared_guard(volatile modern_class* const object) modern_except_state
#ifdef MODERN_GUARDING_ENABLED
	: m_lock(&(object->m_lock))
#endif MODERN_GUARDING_ENABLED
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
#endif MODERN_GUARDING_ENABLED
}

modern_shared_guard::modern_shared_guard(const modern_class* const object) modern_except_state
#ifdef MODERN_GUARDING_ENABLED
	: m_lock(&(object->m_lock))
#endif MODERN_GUARDING_ENABLED
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
#endif MODERN_GUARDING_ENABLED
}

modern_shared_guard::modern_shared_guard(std::atomic<uint64_t>& lock) modern_except_state
{
#ifdef MODERN_GUARDING_ENABLED
	while (m_lock->exchange(modern_guard_status::GUARD_STATUS_READONLY, std::memory_order::memory_order_acquire) > modern_guard_status::GUARD_STATUS_READONLY)
	{
		std::this_thread::yield();
	}
#endif MODERN_GUARDING_ENABLED
}

modern_shared_guard::~modern_shared_guard() modern_except_state
{
#ifdef MODERN_GUARDING_ENABLED
	m_lock->exchange(modern_guard_status::GUARD_STATUS_FREE, std::memory_order::memory_order_release);
#endif MODERN_GUARDING_ENABLED
}
