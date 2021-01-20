#include "FrameLocker.h"


FrameLocker::FrameLocker(const float lock) : m_lock(1 / lock), m_time(0.f), m_deltaTime(0.f)
{

}

FrameLocker::~FrameLocker()
{
}

bool FrameLocker::Run() noexcept
{
	if (m_time >= m_lock)
	{
		m_deltaTime = m_time;
		m_time = 0.f;
		return true;
	}
	m_deltaTime = 0.f;
	return false;
}

void FrameLocker::Update(const float dt) noexcept
{
	m_time += dt;
}

const float FrameLocker::GetDeltaTime() noexcept
{
	return m_deltaTime;
}
