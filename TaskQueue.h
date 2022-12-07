#pragma once
#include "Task.h"
#include <list>

#include <modern__.h>

class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();
	bool Update();
	void Discard();
	void SetTask(class Task* const task);
	void QueueTask(class Task* const task);
	void QueueFrontTask(class Task* const task);
	void Wander(Unit* unit);
	void SetOwner(class Unit* object);
	enum Task::Type GetActiveType() const modern_except_state;
	class Task* const GetActiveTask() const modern_except_state;
private:
	std::list<class Task*> m_tasks;
	class Unit*  m_owner{};
};