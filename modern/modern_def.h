#pragma once
#include <cassert>
#include <sal.h>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstdint>
#include <Windows.h>
#ifdef DrawText
#undef DrawText
#endif
#include <stdio.h>
#include <conio.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <comdef.h>
#include <numeric>

	typedef int64_t modern_Boolean;
#define  modern_int64max (9223372036854775807i64)
#define  modern_false 0ll
#define  modern_true modern_int64max
#define  modern_Boolean_check modern_false <
#define  return_new_reference return * new

#define MODERN_DEBUG_ENABLE_EXCEPTIONS
#ifdef MODERN_DEBUG_ENABLE_EXCEPTIONS
#define modern_except_state
#else
#define modern_except_state noexcept
#endif // MODERN_DEBUG_ENABLE_EXCEPTIONS

#define MODERN_MQUEUE_LOCK_ATOMIC
#ifndef MODERN_MQUEUE_LOCK_ATOMIC
#define MODERN_MQUEUE_LOCK_MUTEX
#endif // !MODERN_MQUEUE_LOCK_ATOMIC


#define modern_thread_safe

	enum MODERN_CONSOLE_TEXT_COLOR
	{
		DARKBLUE = 1,
		DARKGREEN = 2,
		OCEANBLUE = 3,
		DARKRED = 4,
		PURPLE = 5,
		GOLDEN = 6,
		LIGHTGRAY = 7,
		DARKGRAY = 8,
		BLUE = 9,
		LIGHTGREEN = 10,
		LIGHTBLUE = 11,
		RED = 12,
		PINK = 13,
		YELLOW = 14,
		WHITE = 15
	};

