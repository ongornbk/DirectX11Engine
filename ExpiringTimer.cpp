#include "ExpiringTimer.h"

bool ExpiringTimer::update(const float dt)
{
	time -= dt;
	if (time < 0.f)
	{
		action->execute();
		return true;
	}
	return false;
}

ExpiringTimer::ExpiringTimer()
{
	action = nullptr;
	time = 0.f;
}

ExpiringTimer::~ExpiringTimer()
{
	if (action)
	{
		delete action;
		action = nullptr;
	}
}
