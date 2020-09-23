#pragma once
#include "ITimer.h"
class InstantTimer :
	public ITimer
{
	friend class Timer;

	class IAction* action;

	bool update(const float dt) override;

public:

	InstantTimer();
	~InstantTimer();
};

