#include "PeriodicTimer.h"


bool PeriodicTimer::update(const float dt)
{
	time -= dt;
	if (time < 0.f)
	{
		action->execute();
		time = period;
	}
	return false;
}

PeriodicTimer::PeriodicTimer()
{
	action = nullptr;
	time = 0.f;
	period = 0.f;
}

PeriodicTimer::~PeriodicTimer()
{
	if (action)
	{
		delete action;
		action = nullptr;
	}
}
