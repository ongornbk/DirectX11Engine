#pragma once
#include "ITimer.h"

class ITimeTimer
{
protected:
	ITimer* m_me;
public:
	virtual ~ITimeTimer() { ;; }

	[[nodiscard]] virtual const float GetRemainingTime() = 0;
	[[nodiscard]] virtual const float UpdateRemainingTime(const float dt) = 0;
	[[nodiscard]] virtual class ITimer* const GetTimer() = 0;
};