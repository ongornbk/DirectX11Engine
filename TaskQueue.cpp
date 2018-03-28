#include "TaskQueue.h"
#include "GlobalUtilities.h"
#include "Unit.h"

using::GlobalUtilities::random;

XMFLOAT3 _vectorcall RandomizeXMFLOAT3(XMFLOAT3 object, float x, float y) noexcept
{
	float xx = object.x;
	float yy = object.y;
	xx += random(-x, x);
	yy += random(-y, y);
	return XMFLOAT3(xx, yy, 0.0f);
}

TaskQueue::TaskQueue()
{

}


TaskQueue::~TaskQueue()
{
	while (!m_tasks.empty())
	{
		delete m_tasks.front();
		m_tasks.pop();
}
}

void TaskQueue::Discard()
{
	while (!m_tasks.empty())
	{
		delete m_tasks.front();
		m_tasks.pop();
	}
}


bool TaskQueue::Update()
{
	if (!m_tasks.empty())
	{
		if (m_tasks.front()->Update())
		{
			return true;
		}
		else
		{
			delete m_tasks.front();
			m_tasks.pop();
		}
	}
	else
	{
		return false;
	}
}
void TaskQueue::SetTask(Task* task)
{
	Discard();
	m_tasks.push(task);
}
void TaskQueue::QueueTask(Task * task)
{
	m_tasks.push(task);
}
void TaskQueue::Wander(Unit * unit)
{
	Task* task = new Task();
	TaskGotoPoint* tgtp = new TaskGotoPoint();
	tgtp->destination = RandomizeXMFLOAT3(unit->GetPosition(), 300.0f, 300.0f);
	tgtp->object = unit;
	task->m_content.taskGotoPoint = tgtp;
	task->m_type = Task::Type::TASKGOTOPOINT;
	SetTask(task);
}
//
//void TaskQueue::Push(Task task)
//{
//	m_tasks.push(task);
//}
//
////Task::Type TaskQueue::GetCurrentTask()
////{
////	return m_tasks.front().m_type;
////}