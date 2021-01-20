#include "ConstIntegerVariable.h"

ConstIntegerVariable::ConstIntegerVariable(const int32_t __value) : value(__value)
{
}

const int32_t ConstIntegerVariable::get()
{
	return value;
}
