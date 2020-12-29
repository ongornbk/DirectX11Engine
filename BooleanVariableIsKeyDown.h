#pragma once
#include "IBooleanVariable.h"
#include <cstdint>

class BooleanVariableIsKeyDown :
	public IBooleanVariable
{
	uint32_t key;
public:
	BooleanVariableIsKeyDown(const uint32_t __key);
	const bool get() override;
};



