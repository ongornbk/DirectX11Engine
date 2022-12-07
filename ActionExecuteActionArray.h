#pragma once
#include "IAction.h"


class ActionExecuteActionArray :
	public IAction
{
	class modern_array<class IAction*> m_actions;

public:

	ActionExecuteActionArray();
	~ActionExecuteActionArray();

	void push(class IAction* const action);

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

