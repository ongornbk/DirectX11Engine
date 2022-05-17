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

	typedef int64_t modern_Boolean;
#define  modern_false 0ll
