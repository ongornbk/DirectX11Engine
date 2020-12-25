#pragma once
#include "ITimer.h"

class FuzzyTimer :
	public ITimer
{
	friend class Timer;

	class IAction* action;

	float time;

	bool update(const float dt) override;

public:

	FuzzyTimer();
	~FuzzyTimer();
};

