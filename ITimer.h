#pragma once
#include "IAction.h"

class ITimer
{
	friend class Timer;

protected:
	virtual bool update(const float dt) = 0;
	virtual ~ITimer();
};

