#pragma once
#include "ITimer.h"
#include "IAction.h"

class PermanentFuzzyTimer :
	public ITimer
{
	friend class Timer;

	class IAction* actionFuzzy;

	bool update(const float dt) override;

public:

	PermanentFuzzyTimer();
	~PermanentFuzzyTimer();

	void Initialize(class IAction* const fuzzy);
};

