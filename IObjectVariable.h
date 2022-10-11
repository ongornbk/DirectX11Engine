#pragma once
#include "GameObject.h"

class IObjectVariable
{
public:
	virtual const struct RenderObject* const get() = 0;
};
