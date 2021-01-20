#pragma once
#include "IIntegerVariable.h"

class ConstIntegerVariable :
	public IIntegerVariable
{
	int32_t value;
public:
	ConstIntegerVariable(const int32_t __value);
	const int32_t get() override;
};


