#pragma once
#include "modern_def.h"

struct modern_node256
{
    __m256 data;
    struct modern_node256* left;
    struct modern_node256* right;
};