#pragma once
#include <deque>

#include "IAction.h"
#include "ExpiringTimer.h"
#include "PeriodicTimer.h"

class Timer : public ITimer
{
public:

	static void Update(const float dt);
	static void CreateExpiringTimer(class IAction* const action, const float time);
	static void CreatePeriodicTimer(class IAction* const action, const float time, const float period);
};


