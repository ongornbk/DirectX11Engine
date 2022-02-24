#include "FuzzyExpiringTimer.h"

bool FuzzyExpiringTimer::update(const float dt)
{
	time -= dt;
	actionFuzzy->execute();
	if (time < 0.f)
	{
		actionExpiring->execute();
		return true;
	}
	return false;
}

FuzzyExpiringTimer::FuzzyExpiringTimer()
{
	actionFuzzy = nullptr;
	actionExpiring = nullptr;
	time = 0.f;
}

FuzzyExpiringTimer::~FuzzyExpiringTimer()
{
	if (actionFuzzy)
	{
		delete actionFuzzy;
		actionFuzzy = nullptr;
	}
	if (actionExpiring)
	{
		delete actionExpiring;
		actionExpiring = nullptr;
	}
}

void FuzzyExpiringTimer::Initialize(IAction* const fuzzy, IAction* const expiring, const float _time)
{
	actionFuzzy = fuzzy;
	actionExpiring = expiring;
	this->time = _time;
}
