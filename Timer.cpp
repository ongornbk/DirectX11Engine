#include "Timer.h"

namespace
{

	static std::deque<Timer*> m_timers;
}

bool Timer::update(const float dt)
{
	time -= dt;
	return (time < 0.f);
}

Timer::Timer()
{
	action = nullptr;
	time = 0.f;
}

Timer::~Timer()
{
	action->execute();
	delete action;
	action = nullptr;
}

void Timer::Update(const float dt)
{

	for (auto first = m_timers.begin(); first < m_timers.end(); ++first)
	{
		if ((*first)->update(dt))
		{
			delete* first;
			m_timers.erase(first);
		}

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

void Timer::CreateTimer(IAction* const action, const float time)
{
	Timer* timer = new Timer();
	timer->action = action;
	timer->time = time;
	m_timers.push_back(timer);
}
