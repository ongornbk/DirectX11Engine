#include "ConditionTimer.h"
#include "FloatConditionGreater.h"
bool ConditionTimer::update(const float dt)
{

		if (m_condition->CheckCondition())
		{
			m_action->execute();
			//this;
			return true;
		}
		return false;

}

ConditionTimer::ConditionTimer(IAction* const __action, ICondition* const __condition)
{
	m_action = __action;
	m_condition = __condition;
}

ConditionTimer::~ConditionTimer()
{
	if (m_action)
	{
		delete m_action;
		m_action = nullptr;
	}
	if (m_condition)
	{
		delete m_condition;
		m_condition = nullptr;
	}
}