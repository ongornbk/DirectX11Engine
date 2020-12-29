#pragma once
#include "ITimer.h"
#include "ICondition.h"

class ConditionTimer : public ITimer
{
	friend class Timer;

	class IAction* action;
	class ICondition* condition;


	bool update(const float dt) override;

public:

	ConditionTimer();
	~ConditionTimer();
};

