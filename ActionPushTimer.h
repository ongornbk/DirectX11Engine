#pragma once
#include "Timer.h"
#include "ITimer.h"

class ActionPushTimer :
	public IAction
{
	class ITimer* m_timer;

	ActionPushTimer() = delete;

public:

	ActionPushTimer(class ITimer* const timer);
	~ActionPushTimer();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};