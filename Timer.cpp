#include "Timer.h"
#include "GarbageCollector.h"
#include <list>

namespace
{

	static std::list<class ITimer*> m_timers;

}



void Timer::Update(const float dt)
{

	class GarbageCollector* gbc = GarbageCollector::GetInstance();

		for (auto& element = m_timers.begin();element != m_timers.end();element++)
		{
				if ((*element)->update(dt))
				{
					gbc->AsyncDelete(*element);
					m_timers.erase(element);
				}
		}

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

void Timer::CreateInstantTimer(IAction* const action)
{
	class InstantTimer* const timer = new InstantTimer();
	timer->action = action;
	m_timers.push_back(timer);
}
