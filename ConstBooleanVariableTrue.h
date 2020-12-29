#pragma once
#include "IBooleanVariable.h"
class ConstBooleanVariableTrue :
	public IBooleanVariable
{
public:
	const bool get() override;
};

