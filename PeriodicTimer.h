#pragma once
#include "ITimer.h"
class PeriodicTimer :
	public ITimer
{
	friend class Timer;

	float time;
	float period;
	class IAction* action;



	bool update(const float dt) override;

public:

	PeriodicTimer();
	~PeriodicTimer();
};

