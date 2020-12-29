#pragma once
#include <deque>

#include "IAction.h"
#include "ICondition.h"
#include "ExpiringTimer.h"
#include "PeriodicTimer.h"
#include "InstantTimer.h"
#include "FuzzyTimer.h"
#include "ConditionTimer.h"

class Timer : public ITimer
{
public:

	static void Update(const float dt);
	static void CreateExpiringTimer(class IAction* const action, const float time);
	static void CreatePeriodicTimer(class IAction* const action, const float time, const float period);
	static void CreateInstantTimer(class IAction* const action);
	static void CreateFuzzyTimer(class IAction* const action,const float time);
	static void CreateConditionTimer(class IAction* const action,class ICondition* const condition);
};


