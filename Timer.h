#pragma once
#include <deque>

#include "IAction.h"

class Timer
{
	float time;
	class IAction* action;

	
	bool update(const float dt);

	Timer();
	~Timer();

public:

	static void Update(const float dt);
	static void CreateTimer(class IAction* const action, const float time);
};

