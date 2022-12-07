#include "TaskQueue.h"
#include "Unit.h"
#include "GarbageCollector.h"

struct DirectX::XMFLOAT3 _vectorcall RandomizeXMFLOAT3(DirectX::XMFLOAT3 object,const float x,const float y) modern_except_state
{
	float xx = object.x;
	float yy = object.y;
	xx += modern_random(-x, x);
	yy += modern_random(-y, y);
	return DirectX::XMFLOAT3(xx, yy, object.z);
}

TaskQueue::TaskQueue()
{

}


TaskQueue::~TaskQueue()
{
//	Task* task = (Task*)m_tasks.pop();
//	while (task)
//	{
//		task->Release();
//		//m_tasks.pop();
//		task = (Task*)m_tasks.pop();
//}
	for (auto& obj : m_tasks)
	{
		obj->Release();
	}
}

void TaskQueue::Discard()
{
	//Task* task = (Task*)m_tasks.pop();
	//while (task)
	//{
	//	//GarbageCollector::GetInstance()->AsyncDelete(m_tasks.front());
	//	//m_tasks.front();
	//	task->Release();
	//	task = (Task*)m_tasks.pop();
	//}
	//if (m_owner)
	//	m_owner->EndRunning();

	for (auto& obj : m_tasks)
	{
		obj->Release();
	}
	m_tasks.clear();
}


bool TaskQueue::Update()
{
	//Task*
	Task* task = (Task*)m_tasks.front();
	if (m_tasks.size())
	{
		if (task->Update())
		{
			return true;
		}
		else
		{
			{
				//class Task* const task = m_tasks.front();
				//if (task->m_stance == Task::Stance::TSRUNNING)
				//{
					//if (m_owner)
					//	m_owner->EndRunning();
				//}
				task->Release();
				m_tasks.pop_front();
				//m_tasks.pop();
			}
			//if (m_tasks.size())
			//{
			//	Task* task = m_tasks.front();
			//	if (task->m_stance == Task::Stance::TSRUNNING)
			//	{
			//		if (m_owner)
			//			m_owner->BeginRunning();
			//	}
			//}
		}
	}
		return false;

}
void TaskQueue::SetTask(
	class Task* const task
)
{
	Discard();
	m_tasks.push_back(task);
	//if (m_owner&&task->m_stance == Task::Stance::TSRUNNING)
	//	m_owner->BeginRunning();
}
void TaskQueue::QueueTask(Task * task)
{
	m_tasks.push_back(task);
}
void TaskQueue::QueueFrontTask(Task* const task)
{
	m_tasks.push_front(task);
}
void TaskQueue::Wander(Unit * unit)
{
	class TaskGotoPoint* task = new TaskGotoPoint();
	task->destination = RandomizeXMFLOAT3(unit->GetPosition(), 600.0f, 600.0f);
	task->object.make_handle(unit->GetHandle());
	QueueTask(task);
}

void TaskQueue::SetOwner(Unit * object)
{
	m_owner = object;
}

Task::Type TaskQueue::GetActiveType() const modern_except_state
{
	if (m_tasks.size())
		return ((Task*)m_tasks.front())->m_type;
	else
		return Task::Type::NONE;
}

Task* const TaskQueue::GetActiveTask() const modern_except_state
{
	if (m_tasks.size())
		return ((Task*)m_tasks.front());
	else return nullptr;
}
