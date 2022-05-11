#pragma once
#include "Task.h"
#include "modern/modern_queue.h"
#include <list>

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
	enum Task::Type GetActiveType() const noexcept;
	class Task* const GetActiveTask() const noexcept;
private:
	std::list<class Task*> m_tasks;
	class Unit*  m_owner{};
};