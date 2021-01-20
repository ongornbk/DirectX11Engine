#include "ConstObjectVariable.h"

ConstObjectVariable::ConstObjectVariable(struct RenderObject* const __value) : value(__value)
{
}

struct RenderObject* const ConstObjectVariable::get()
{
	return value;
}
