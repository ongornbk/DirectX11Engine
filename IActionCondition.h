#pragma once
#include "ICondition.h"

class IActionCondition
{
public:
	virtual class ICondition* const GetCondition() = 0;
};

