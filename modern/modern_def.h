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


