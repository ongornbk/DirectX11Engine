#pragma once
#include "ActionType.h"

class IActionSplitArrayBehavior
{
public:
	virtual ~IActionSplitArrayBehavior();
	virtual const enum class ActionType GetType() = 0;
};

