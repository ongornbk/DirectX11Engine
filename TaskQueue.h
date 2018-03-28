#pragma once
#include "Task.h"
#include <queue>
using std::queue;

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
private:
	queue<Task*> m_tasks;
};