#pragma once
#include <deque>

#include "IAction.h"
#include "ICondition.h"
#include "ExpiringTimer.h"
#include "PeriodicTimer.h"
#include "InstantTimer.h"
#include "FuzzyTimer.h"
#include "ConditionTimer.h"
#include "FuzzyExpiringTimer.h"

class Timer : public ITimer
{
public:
	static void Initialize();
	static void Update(const float dt);
	static void Update2μs(const float dt);
	static void Update1s(const float dt);
	static void UpdatePostSort(const float dt);
	static void Push(class ITimer* const timer);
	static void CreateExpiringTimer(class IAction* const action, const float time);
	static void CreatePeriodicTimer(class IAction* const action, const float time, const float period);
	static void CreateInstantTimer(class IAction* const action);
	static void CreatePostSortInstantTimer(class IAction* const action);
	static void CreateFuzzyTimer(class IAction* const action,const float time);
	static void CreateFuzzyExpiringTimer(class IAction* const actionFuzzy, class IAction* const actionExpiring, const float time);
	static void CreateConditionTimer(class IAction* const action,class ICondition* const condition);

	static size_t CountTimers();
	static size_t CountSleepingTimers();
};


