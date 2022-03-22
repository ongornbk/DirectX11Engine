#pragma once
#include "Task.h"
#include "modern/modern_queue.h"

class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();
	bool Update();
	void Discard();
	void SetTask(Task* task);
	void QueueTask(Task* task);
	void Wander(Unit* unit);
	void SetOwner(class Unit* object);
	enum Task::Type GetActiveType() const noexcept;
	class Task* const GetActiveTask() const noexcept;
private:
	modern_queue m_tasks;
	class Unit*  m_owner{};
};