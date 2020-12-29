#include "ConditionTimer.h"

bool ConditionTimer::update(const float dt)
{
	if (condition->CheckCondition())
	{
		action->execute();
		return true;
	}
	return false;
}

ConditionTimer::ConditionTimer()
{
	action = nullptr;
	condition = nullptr;
}

ConditionTimer::~ConditionTimer()
{
	if (action)
	{
		delete action;
		action = nullptr;
	}
	if (condition)
	{
		delete condition;
		condition = nullptr;
	}
}