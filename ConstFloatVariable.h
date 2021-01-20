#pragma once
#include "IFloatVariable.h"

class ConstFloatVariable :
	public IFloatVariable
{
	float value;
public:
	ConstFloatVariable(const float __value);
	const float get() override;
};


