#pragma once
#include "IAction.h"

class ActionSkipRemainingActions :
	public IAction
{

public:

	ActionSkipRemainingActions();
	~ActionSkipRemainingActions();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};


