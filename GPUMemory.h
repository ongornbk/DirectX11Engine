#pragma once

#include <modern__.h>

class GPUMemory : public modern_class
{
public:
	static void Initialize() modern_except_state;
	static struct modern_class* const get() modern_except_state;
};

