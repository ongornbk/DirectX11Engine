#pragma once
#include "IBooleanVariable.h"
class ConstBooleanVariableFalse :
	public IBooleanVariable
{
public:
	const bool get() override;
};

