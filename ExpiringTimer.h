#pragma once
//#include "ITimer.h"
#include "ITimeTimer.h"

class ExpiringTimer :
	public ITimer,
	public ITimeTimer
{
	friend class Timer;

	float time;
	class IAction* action;



	bool update(const float dt) override;

	[[nodiscard]] const float GetRemainingTime() override;
	[[nodiscard]] const float UpdateRemainingTime(const float dt) override;
	[[nodiscard]] class ITimer* const GetTimer() override;

public:

	ExpiringTimer();
	~ExpiringTimer();
};

