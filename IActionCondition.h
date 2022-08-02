#pragma once
#include "ICondition.h"

class IActionCondition
{
public:
	virtual ~IActionCondition();
	virtual class ICondition* const GetCondition() = 0;
};

