#include "ActionExecuteAction.h"

ActionExecuteAction::ActionExecuteAction(IAction* action) : m_action(action)
{
}

ActionExecuteAction::~ActionExecuteAction()
{
	if (m_action)
		delete m_action;
}

void ActionExecuteAction::execute()
{
	if (m_action)
		m_action->execute();
}

const ActionBehavior ActionExecuteAction::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
