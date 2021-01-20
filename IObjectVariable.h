#pragma once
#include "RenderContainer.h"

class IObjectVariable
{
public:
	virtual const struct RenderObject* const get() = 0;
};
