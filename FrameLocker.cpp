#include "FrameLocker.h"


FrameLocker::FrameLocker(const float lock) : 
	m_lock(1 / lock),
	m_time(0.f),
	m_deltaTime(0.f),
	m_state(false)
{

}

FrameLocker::~FrameLocker()
{
}

bool FrameLocker::Run() modern_except_state
{
	if (m_time >= m_lock)
	{
		m_deltaTime = m_time;
		m_time = 0.f;
		m_state = true;
		return true;
	}
	m_deltaTime = 0.f;
	m_state = false;
	return false;
}

bool FrameLocker::State() const modern_except_state
{
	return m_state;
}

void FrameLocker::Update(const float dt) modern_except_state
{
	m_time += dt;
}

const float FrameLocker::GetDeltaTime() modern_except_state
{
	return m_deltaTime;
}
