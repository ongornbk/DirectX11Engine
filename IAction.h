#pragma once
#include "ActionStance.h"
#include "ActionBehavior.h"

#include <modern__.h>

class IAction
{
protected:
	//enum class ActionStance m_stance;
public:
	virtual ~IAction();
	virtual void execute() = 0;
	virtual const enum class ActionBehavior execute_in_array() = 0;
};

