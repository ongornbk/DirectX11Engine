#include "Timer.h"
#include "GarbageCollector.h"
#include <list>
#include <atomic>
#include <iostream>

namespace
{
	static std::list<class ITimer*> m_stoppedTimers;
	static std::list<class ITimer*> m_timers;
	static std::list<class ITimer*> m_timersPostSort;
	static std::list<class ITimer*> m_echoTimers;
	static std::atomic<int64_t> m_stance = 0;
}



void Timer::Update(const float dt)
{
	m_stance.store(1, std::memory_order::memory_order_seq_cst);

		for (auto& element = m_timers.begin();element != m_timers.end();element++)
		{
				if ((*element)->update(dt))
				{
					//gbc->AsyncDelete(*element);
					//std::cout << "fddff" << std::endl;
					//delete(ITimer*)(* element);
					delete *element;
					m_timers.erase(element);
				}
		}

		m_stance.store(0, std::memory_order::memory_order_seq_cst);

		m_timers.merge(m_echoTimers);
}

void Timer::UpdatePostSort(const float dt)
{
	for (auto& element = m_timersPostSort.begin(); element != m_timersPostSort.end(); element++)
	{
		if ((*element)->update(dt))
		{
			//gbc->AsyncDelete(*element);
			//std::cout << "fddff" << std::endl;
			//delete(ITimer*)(* element);
			delete* element;
			m_timers.erase(element);
		}
	}
}

void Timer::Push(ITimer* const timer)
{
	if (!timer)
		return;
	if (m_stance.load() == 0)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateExpiringTimer(class IAction* const action, const float time)
{
	class ExpiringTimer* const timer = new ExpiringTimer();
	timer->action = action;
	timer->time = time;
	if (m_stance.load() == 0)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreatePeriodicTimer(IAction* const action, const float time,const float period)
{
	class PeriodicTimer* const timer = new PeriodicTimer();
	timer->action = action;
	timer->time = time;
	timer->period = period;
	if (m_stance.load() == 0)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateInstantTimer(IAction* const action)
{
	class InstantTimer* const timer = new class InstantTimer();
	timer->action = action;
	if (m_stance.load() == 0)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreatePostSortInstantTimer(IAction* const action)
{
	class InstantTimer* const timer = new class InstantTimer();
	timer->action = action;
		m_timersPostSort.push_back(timer);
}



void Timer::CreateFuzzyTimer(IAction* const action, const float time)
{
	class FuzzyTimer* const timer = new FuzzyTimer();
	timer->action = action;
	timer->time = time;
	if (m_stance.load() == 0)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateFuzzyExpiringTimer(IAction* const actionFuzzy, IAction* const actionExpiring, const float time)
{
	class FuzzyExpiringTimer* const timer = new FuzzyExpiringTimer();
	timer->actionFuzzy = actionFuzzy;
	timer->actionExpiring = actionExpiring;
	timer->time = time;
	if (m_stance.load() == 0)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateConditionTimer(IAction* const action, ICondition* const condition)
{
	class ConditionTimer* const timer = new ConditionTimer();
	timer->action = action;
	timer->condition = condition;
	if (m_stance.load() == 0)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

size_t Timer::CountTimers()
{
	return m_timers.size();
}
