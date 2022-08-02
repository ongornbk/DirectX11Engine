#include "ConstFloatVariable.h"

ConstFloatVariable::ConstFloatVariable(const float __value)
{
	value = __value;
}

const float ConstFloatVariable::get()
{
	return value;
}
