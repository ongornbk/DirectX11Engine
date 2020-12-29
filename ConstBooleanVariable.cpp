#include "ConstBooleanVariable.h"

ConstBooleanVariable::ConstBooleanVariable(const bool __value) : value(__value)
{
}

const bool ConstBooleanVariable::get()
{
	return value;
}
