#pragma once
#include "ITimer.h"
class ExpiringTimer :
	public ITimer
{
	friend class Timer;

	float time;
	class IAction* action;



	bool update(const float dt) override;

public:

	ExpiringTimer();
	~ExpiringTimer();
};

