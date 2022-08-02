#include "modern_framelock.h"

modern_framelock::modern_framelock(const double lock) : 
m_lock(1.0 / lock),
m_time(0.0),
m_deltaTime(0.0),
m_state(0ll)
{
}

modern_framelock::~modern_framelock()
{

}

const modern_Boolean modern_framelock::Run() modern_except_state
{
	if (m_time >= m_lock)
	{
		m_deltaTime = m_time;
		m_time = 0.0;
		m_state = 1ll;
		return 1ll;
	}
	m_deltaTime = 0.0;
	m_state = 0ll;
	return 0ll;
}

const modern_Boolean modern_framelock::State() const modern_except_state
{
	return m_state;
}

void modern_framelock::Update(const double dt) modern_except_state
{
	m_time += dt;
}

const double modern_framelock::GetDeltaTime() modern_except_state
{
	return m_deltaTime;
}
