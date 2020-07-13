#pragma once
#include "IAction.h"
#include "modern/modern.h"

class ActionExecuteActionArray :
	public IAction
{
	class modern_array<class IAction*> m_actions;

public:

	ActionExecuteActionArray();
	~ActionExecuteActionArray();

	void push(class IAction* const action);

	void execute() override;
};

