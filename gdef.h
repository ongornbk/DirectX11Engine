#pragma once
#include <cstdint>
#include <stdio.h>
#include <sal.h>
#include "modern/modern_def.h"

typedef uint64_t uint64;
typedef int64_t  int64;
typedef uint32_t uint32;
typedef int32_t  int32;
typedef uint16_t uint16;
typedef int16_t  int16;
typedef int8_t   int8;
typedef uint8_t  uint8;

typedef uint8_t BYTE;

#ifdef _MSC_VER
#define MSVC_VOLATILE volatile
#else
#define MSVC_VOLATILE
#endif

