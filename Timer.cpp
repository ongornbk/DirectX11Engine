#include "Timer.h"

namespace
{

	static std::deque<class ITimer*> m_timers;
}



void Timer::Update(const float dt)
{

	for (auto first = m_timers.begin(); first < m_timers.end(); ++first)
	{
	if((*first)->update(dt))
				m_timers.erase(first);
	}

	//for (auto timer : m_timers)
	//{
		//if (timer->update(dt))
		//{
			//delete timer;
			//m_timers.erase()
		//}
//	}
}

void Timer::CreateExpiringTimer(IAction* const action, const float time)
{
	class ExpiringTimer* const timer = new ExpiringTimer();
	timer->action = action;
	timer->time = time;
	m_timers.push_back(timer);
}

void Timer::CreatePeriodicTimer(IAction* const action, const float time,const float period)
{
	class PeriodicTimer* const timer = new PeriodicTimer();
	timer->action = action;
	timer->time = time;
	timer->period = period;
	m_timers.push_back(timer);
}
