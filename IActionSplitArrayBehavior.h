#pragma once
#include "ActionType.h"

class IActionSplitArrayBehavior
{
public:
	virtual const enum class ActionType GetType() = 0;
};

