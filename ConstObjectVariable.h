#pragma once
#include "IObjectVariable.h"

class ConstObjectVariable :
	public IObjectVariable
{
	struct RenderObject*  value;
public:
	ConstObjectVariable(struct RenderObject* const __value);
	struct RenderObject* const get() override;
};

