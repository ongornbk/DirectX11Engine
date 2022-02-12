#pragma once
#include "ITimer.h"

class FuzzyExpiringTimer :
	public ITimer
{
	friend class Timer;

	class IAction* actionFuzzy;
	class IAction* actionExpiring;

	float time;

	bool update(const float dt) override;

public:

	FuzzyExpiringTimer();
	~FuzzyExpiringTimer();
};

