#include "Timer.h"
#include "GarbageCollector.h"
#include <list>
#include <atomic>
#include <iostream>
#include "ConditionFactory.h"

namespace
{
	//static std::list<class ITimer*> m_stoppedTimers;
	//static std::<class ITimer*> m_timers;
	static modern_array<class ITimer*> m_timers;
	//static std::list<class ITimer*> m_timersPostSort;
	static modern_array<class ITimer*> m_echoTimers;
	static std::atomic<int64_t> m_stance = 0ll;
}



void Timer::Update(const float dt)
{
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
	if (m_stance.load() == 0ll)
		m_timers.push_back(timer);
	else m_echoTimers.push_back(timer);
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
