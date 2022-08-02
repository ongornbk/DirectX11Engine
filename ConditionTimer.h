#pragma once
#include "ITimer.h"
#include "ICondition.h"

class ConditionTimer : public ITimer
{
	friend class Timer;

	class IAction* m_action;
	class ICondition* m_condition;


	bool update(const float dt) override;

public:

	ConditionTimer(class IAction* const __action,class ICondition* const __condition);
	~ConditionTimer();
};

