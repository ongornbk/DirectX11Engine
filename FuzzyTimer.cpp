#include "FuzzyTimer.h"

bool FuzzyTimer::update(const float dt)
{
	time -= dt;
	action->execute();
	if (time < 0.f)
	{
		return true;
	}
	return false;
}

FuzzyTimer::FuzzyTimer()
{
	action = nullptr;
	time = 0.f;
}

FuzzyTimer::~FuzzyTimer()
{
	if (action)
	{
		delete action;
		action = nullptr;
	}
}
