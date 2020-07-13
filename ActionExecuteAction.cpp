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
