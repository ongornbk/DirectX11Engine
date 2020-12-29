#include "ActionWait.h"

ActionWait::ActionWait(float duration) :  m_duration(duration)
{
}

ActionWait::~ActionWait()
{
}

void ActionWait::execute()
{
	//WHY??
}

const ActionBehavior ActionWait::execute_in_array()
{
	//this->execute(); WHY??
	return ActionBehavior::ACTION_BEHAVIOR_SPLITARRAY;
}

const ActionType ActionWait::GetType()
{
	return ActionType::ACTION_TYPE_TIMER;
}

const float ActionWait::GetDuration()
{
	return m_duration;
}
