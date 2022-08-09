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

const float ExpiringTimer::GetRemainingTime()
{
	return time;
}

const float ExpiringTimer::UpdateRemainingTime(const float dt)
{
	time -= dt;
	if (time < 0.f)
	{
		action->execute();
	}
	return time;
}

class ITimer* const ExpiringTimer::GetTimer()
{
	return m_me;
}

ExpiringTimer::ExpiringTimer()
{
	m_me = this;
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
