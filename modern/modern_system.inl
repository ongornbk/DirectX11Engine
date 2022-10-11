#include "modern_system.h"
#pragma once

inline const int32_t __stdcall modern_system_get_screen_width()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

inline const int32_t __stdcall modern_system_get_screen_height()
{
	return GetSystemMetrics(SM_CYSCREEN);
}
