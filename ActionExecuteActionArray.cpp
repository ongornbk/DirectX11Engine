#include "ActionExecuteActionArray.h"

ActionExecuteActionArray::ActionExecuteActionArray()
{
}

ActionExecuteActionArray::~ActionExecuteActionArray()
{
}

void ActionExecuteActionArray::push(class IAction* const action)
{
	if (action)
		m_actions.push_back(action);
}

void ActionExecuteActionArray::execute()
{
	for (auto& ele : m_actions)
		ele->execute();
}
