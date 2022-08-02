#pragma once
#include "modern/modern_def.h"

class FrameLocker
{
	bool  m_state;
	double m_lock;
	double m_time;
	double m_deltaTime;
public:
	FrameLocker(const float lock);
	~FrameLocker();

	bool Run() modern_except_state;
	bool State() const modern_except_state;
	void Update(const float dt) modern_except_state;
	const float GetDeltaTime() modern_except_state;
};

