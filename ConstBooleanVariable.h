#pragma once
#include "IBooleanVariable.h"

class ConstBooleanVariable :
	public IBooleanVariable
{
	bool value;
public:
	ConstBooleanVariable(const bool __value);
	const bool get() override;
};

