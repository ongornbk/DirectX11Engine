#pragma once
#include <cstdint>

typedef int32_t Boolean;

#define CheckBoolean(name) if(!SUCCEEDED(name##)) return name