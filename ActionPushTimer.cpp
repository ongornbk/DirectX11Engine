#include "ActionPushTimer.h"

ActionPushTimer::ActionPushTimer(class ITimer* const timer)
{
	m_timer = timer;
}

ActionPushTimer::~ActionPushTimer()
{
	//if (m_action)
		//delete m_action;
}

void ActionPushTimer::execute()
{
	Timer::Push(m_timer);
}

const ActionBehavior ActionPushTimer::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
