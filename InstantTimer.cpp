#include "InstantTimer.h"

bool InstantTimer::update(const float dt)
{
	action->execute();
	return true;
}

InstantTimer::InstantTimer()
{
	action = nullptr;
}

InstantTimer::~InstantTimer()
{
	if (action)
	{
		delete action;
		action = nullptr;
	}
}
