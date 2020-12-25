#pragma once
#include "IAction.h"

class ActionExecuteAction :
	public IAction
{
	class IAction* m_action;

	ActionExecuteAction() = delete;

public:

	ActionExecuteAction(class IAction* action);
	~ActionExecuteAction();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};



