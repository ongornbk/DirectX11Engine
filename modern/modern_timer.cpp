#include "modern_timer.h"
#include <iostream>

modern_timer::modern_timer()
{
	m_start = modern_timer::now();
	m_stop = modern_timer::now();
}

modern_timer::~modern_timer()
{
}

void modern_timer::Restart()
{
	m_running = 1ll;
	m_start = modern_timer::now();
}

modern_Boolean modern_timer::Stop()
{
	if (!m_running)
		return 0ll;
	else
	{
		m_stop = modern_timer::now();
		m_running = 0ll;
		return 1ll;
	}
}

modern_Boolean modern_timer::Start()
{
	if (m_running)
	{
		return 0ll;
	}
	else
	{
		m_start = modern_timer::now();
		m_running = 1ll;
		return 0ll;
	}
}

double modern_timer::GetDeltaTime()
{
	if (m_running)
	{
		modern_duration elapsed = modern_duration(modern_timer::now() - m_start);
		return elapsed.count();
	}
	else
	{
		modern_duration elapsed = modern_duration(m_stop - m_start);
		return elapsed.count();
	}
}

modern_timepoint const modern_timer::now()
{
	return std::chrono::high_resolution_clock::now();
}
