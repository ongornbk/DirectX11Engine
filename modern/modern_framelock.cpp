#include "modern_framelock.h"

modern_framelock::modern_framelock(const double lock) : 
m_lock(1.0 / lock),
m_time(0.0),
m_deltaTime(0.0),
m_state(0)
{
}

modern_framelock::~modern_framelock()
{

}

const modern_Boolean modern_framelock::Run() noexcept
{
	if (m_time >= m_lock)
	{
		m_deltaTime = m_time;
		m_time = 0.0;
		m_state = 1;
		return 1;
	}
	m_deltaTime = 0.0;
	m_state = 0;
	return 0;
}

const modern_Boolean modern_framelock::State() const noexcept
{
	return m_state;
}

void modern_framelock::Update(const double dt) noexcept
{
	m_time += dt;
}

const double modern_framelock::GetDeltaTime() noexcept
{
	return m_deltaTime;
}
