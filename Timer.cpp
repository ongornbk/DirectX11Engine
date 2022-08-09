#include "Timer.h"
#include "GarbageCollector.h"
#include "ActionExecuteCFunction.h"
#include <list>
#include <atomic>
#include <iostream>
#include "ConditionFactory.h"

namespace
{
	//static std::list<class ITimer*> m_stoppedTimers;
	//static std::<class ITimer*> m_timers;
	static modern_array<class ITimer*> m_timers;
	static modern_array<class ITimeTimer*> m_microsecondTimers;
	static modern_array<class ITimeTimer*> m_secondTimers;
	//static std::list<class ITimer*> m_timersPostSort;
	static modern_array<class ITimer*> m_echoTimers;
	static std::atomic<int64_t> m_stance = 0ll;

	static volatile float m_dt;
	static volatile float m_ddt2;
	static volatile float m_ddt100;
}

extern "C"
{
	static void TimerUpdate2(void)
	{
		Timer::Update1s(m_ddt100);
		m_ddt100 = 0.f;
		Timer::Update2μs(m_ddt2);
		m_ddt2 = 0.f;
	}
}



void Timer::Initialize()
{
	class PeriodicTimer* const timer2 = new PeriodicTimer();
	timer2->action = new ActionExecuteCFunction(TimerUpdate2);
	m_timers.push_back(timer2);
}

void Timer::Update(const float dt)
{
	m_dt = dt;
	m_ddt2 += dt;
	m_ddt100 += dt;

	m_stance.store(1ll, std::memory_order::memory_order_seq_cst);

		//for (auto&& element = m_timers.begin();element != m_timers.end();element++)
		//{
		//	OutputDebugString(typeid(**element).name() + '\n');
		//		if ((*element)->update(dt))
		//		{
		//			//gbc->AsyncDelete(*element);
		//			//std::cout << "fddff" << std::endl;
		//			//delete(ITimer*)(* element);
		//			delete *element;
		//			m_timers.erase(element);
		//		}
		//}

	for (size_t i = 0ull; i < m_timers.size(); ++i)
	{

		if(m_timers[i])
		if (m_timers[i]->update(dt))
		{
			delete m_timers[i];
			m_timers[i] = nullptr;
			m_timers.remove(i);
			//i--;
		}
	}

	for (size_t i = 0ull; i < m_echoTimers.size(); ++i)
	{
		m_timers.push_back(m_echoTimers[i]);
	}

	m_echoTimers.clear();
	
	//std::swap(m_ti)

		//m_timers.clear();

		//m_timers.merge(m_echoTimers);

		m_stance.store(0ll, std::memory_order::memory_order_seq_cst);
}

void Timer::Update2μs(const float dt)
{
	for (size_t i = 0ull; i < m_microsecondTimers.size(); ++i)
	{

		if (m_microsecondTimers[i])
		{
			const float remainingTime = m_microsecondTimers[i]->UpdateRemainingTime(dt);
			if (remainingTime > 0.f)
			{
				if (remainingTime > dt)
				{
					m_timers.push_back(m_microsecondTimers[i]->GetTimer());
					m_microsecondTimers[i] = nullptr;
					m_microsecondTimers.remove(i);
				}
				//i--;
			}
			else
			{
				delete m_microsecondTimers[i];
				m_microsecondTimers[i] = nullptr;
				m_microsecondTimers.remove(i);
			}
		}
	}
}

void Timer::Update1s(const float dt)
{
	for (size_t i = 0ull; i < m_secondTimers.size(); ++i)
	{

		if (m_secondTimers[i])
		{
			const float remainingTime = m_secondTimers[i]->UpdateRemainingTime(dt);
			if (remainingTime > 0.f)
			{
				if (remainingTime > dt)
				{
					m_microsecondTimers.push_back(m_secondTimers[i]);
					m_secondTimers[i] = nullptr;
					m_secondTimers.remove(i);
				}
				//i--;
			}
			else
			{
				delete m_secondTimers[i];
				m_secondTimers[i] = nullptr;
				m_secondTimers.remove(i);
			}
		}
	}
}

void Timer::UpdatePostSort(const float dt)
{
	//for (auto& element = m_timersPostSort.begin(); element != m_timersPostSort.end(); element++)
	//{
	//	if ((*element)->update(dt))
	//	{
	//		//gbc->AsyncDelete(*element);
	//		//std::cout << "fddff" << std::endl;
	//		//delete(ITimer*)(* element);
	//		delete* element;
	//		m_timers.erase(element);
	//	}
	//}
}

void Timer::Push(ITimer* const timer)
{
	if (!timer)
		return;
	if (m_stance.load() == 0ll)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateExpiringTimer(class IAction* const action, const float time)
{
	//OutputDebugString(typeid(*action).name() + '\n');
	class ExpiringTimer* const timer = new ExpiringTimer();
	timer->action = action;
	timer->time = time;
	if (time > 1.f)
	{
		m_secondTimers.push_back(timer);
	}
	else 
	if (time > 0.02f)
	{
		m_microsecondTimers.push_back(timer);
	}
	else
	{
		if (m_stance.load() == 0ll)
			m_timers.push_back(timer);
		else m_echoTimers.push_back(timer);
	}
}

void Timer::CreatePeriodicTimer(IAction* const action, const float time,const float period)
{
	//OutputDebugString(typeid(*action).name() + '\n');
	class PeriodicTimer* const timer = new PeriodicTimer();
	timer->action = action;
	timer->time = time;
	timer->period = period;
	if (m_stance.load() == 0ll)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateInstantTimer(IAction* const action)
{
	//OutputDebugString(typeid(*action).name() + '\n');
	class InstantTimer* const timer = new class InstantTimer();
	timer->action = action;
	if (m_stance.load() == 0ll)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreatePostSortInstantTimer(IAction* const action)
{
//	class InstantTimer* const timer = new class InstantTimer();
	//timer->action = action;
	//	m_timersPostSort.push_back(timer);
}



void Timer::CreateFuzzyTimer(IAction* const action, const float time)
{
	//OutputDebugString(typeid(*action).name() + '\n');
	class FuzzyTimer* const timer = new FuzzyTimer();
	timer->action = action;
	timer->time = time;
	if (m_stance.load() == 0ll)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateFuzzyExpiringTimer(IAction* const actionFuzzy, IAction* const actionExpiring, const float time)
{
	//OutputDebugString(typeid(action).name());
	class FuzzyExpiringTimer* const timer = new FuzzyExpiringTimer();
	timer->actionFuzzy = actionFuzzy;
	timer->actionExpiring = actionExpiring;
	timer->time = time;
	if (m_stance.load() == 0ll)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
}

void Timer::CreateConditionTimer(IAction* const action, ICondition* const condition)
{
	//OutputDebugString(typeid(*action).name() + '\n');
	if (action && condition)
	{
		class ConditionTimer* const timer = new ConditionTimer(action, condition);
		if (m_stance.load() == 0ll)
			m_timers.push_back(timer);
		else m_echoTimers.push_back(timer);
	}
		//delete timer;
}

size_t Timer::CountTimers()
{
	return m_timers.size();
}

size_t Timer::CountSleepingTimers()
{
	return m_secondTimers.size() + m_microsecondTimers.size();
}
