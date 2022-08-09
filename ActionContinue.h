#pragma once
#include "IAction.h"

class ActionContinue :
	public IAction
{
public:
	[[nodiscard]]ActionContinue();
	~ActionContinue();

	void execute() override;

	const enum class ActionBehavior execute_in_array() override;
};

