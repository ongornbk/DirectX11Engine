#include "TaskPack.h"

TaskPack::TaskPack()
{

}

TaskPack::~TaskPack()
{

}

void TaskPack::execute()
{
	for (size_t i = 0ull; i < m_tasks.size(); ++i)
	{
		m_tasks[i]->execute();
		delete m_tasks[i];
	}
}

void TaskPack::pack(ITask* const task)
{
	m_tasks.push_back(task);
}
