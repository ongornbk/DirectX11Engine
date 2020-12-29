#include "ActionWaitUntil.h"
#include <cassert>

ActionWaitUntil::ActionWaitUntil(class ICondition* const condition) : m_condition(condition)
{
	assert(condition);
}

ActionWaitUntil::~ActionWaitUntil()
{
	if (m_condition)
	{
		delete m_condition;
		m_condition = nullptr;
	}
}

void ActionWaitUntil::execute()
{
	//WHY??
}

const ActionBehavior ActionWaitUntil::execute_in_array()
{
	//this->execute(); WHY??
	return ActionBehavior::ACTION_BEHAVIOR_SPLITARRAY;
}

const ActionType ActionWaitUntil::GetType()
{
	return ActionType::ACTION_TYPE_CONDITION;
}

class ICondition* const ActionWaitUntil::GetCondition()
{
	return m_condition;
}