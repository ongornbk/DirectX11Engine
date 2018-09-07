#pragma once
#include <vector>
#include <utility>

class TimeEvent
{
private:
public:
	TimeEvent();
	~TimeEvent();

};

class EventListener
{
private:
	std::vector<TimeEvent> m_timeEvents;
public:
	EventListener();
	~EventListener();

	void Update(float dt);
};

