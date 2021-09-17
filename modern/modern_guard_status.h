#pragma once
#include "modern_def.h"

enum modern_guard_status
{
	GUARD_STATUS_FREE = 0,
	GUARD_STATUS_READONLY = 1,
	GUARD_STATUS_LOCKED = 2,
	GUARD_STATUS_BLOCKED = 3,
};