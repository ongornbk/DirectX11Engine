#include "TaskQueue.h"
#include "GlobalUtilities.h"
#include "Unit.h"
#include "GarbageCollector.h"
#include "modern/modern.h"

using::GlobalUtilities::random;

DirectX::XMFLOAT3 _vectorcall RandomizeXMFLOAT3(DirectX::XMFLOAT3 object,const float x,const float y) noexcept
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
	while (!m_tasks.empty())
	{
		m_tasks.front()->Release();
		m_tasks.pop();
}
}

void TaskQueue::Discard()
{
	while (!m_tasks.empty())
	{
		//GarbageCollector::GetInstance()->AsyncDelete(m_tasks.front());
		m_tasks.front()->Release();
		m_tasks.pop();
	}
	//if (m_owner)
	//	m_owner->EndRunning();
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
			{
				//class Task* const task = m_tasks.front();
				//if (task->m_stance == Task::Stance::TSRUNNING)
				//{
					//if (m_owner)
					//	m_owner->EndRunning();
				//}
				m_tasks.front()->Release();
				m_tasks.pop();
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
	m_tasks.push(task);
	//if (m_owner&&task->m_stance == Task::Stance::TSRUNNING)
	//	m_owner->BeginRunning();
}
void TaskQueue::QueueTask(Task * task)
{
	m_tasks.push(task);
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

Task::Type TaskQueue::GetActiveType() const noexcept
{
	if (m_tasks.empty())
		return Task::Type::NONE;
	else
		return m_tasks.front()->m_type;
}

Task* const TaskQueue::GetActiveTask() const noexcept
{
	if (m_tasks.empty())
		return nullptr;
	else return m_tasks.front();
}
