#pragma once
#include <cstdint>

class IIntegerVariable
{
public:
	virtual const int32_t get() = 0;
};

