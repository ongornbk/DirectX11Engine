#include "Task.h"
#include "SettingsC.h"
#include <cmath>
#include "Unit.h"


//
//struct TaskFollow
//{
//#define FOLLOWDISTANCE 200.0f
//	bool          Update();
//	Unit*         object;
//	atomic<Unit*> target;
//};
//
//struct TaskAttack
//{
//	bool          Update();
//	Unit*         object;
//	atomic<Unit*> target;
//};
//

//
//struct TaskFleeFromUnit
//{
//	bool          Update();
//	Unit*         object;
//	atomic<Unit*> target;
//};
//
//struct TaskFleeFromPoint
//{
//	bool     Update();
//	Unit*    object;
//	XMFLOAT3 pointA;
//};
//
//struct TaskDefendUnit
//{
//	bool          Update();
//	Unit*         object;
//	atomic<Unit*> target;
//};
//
//
//struct Task
//{
//	union Content
//	{
//		TaskGotoPoint*     taskGotoPoint;
//		TaskPatrol*        taskPatrol;
//		TaskFollow*        taskFollow;
//		TaskAttack*        taskAttack;
//		TaskWander*        taskWander;
//		TaskFleeFromUnit*  taskFleeFromUnit;
//		TaskFleeFromPoint* taskFleeFromPoint;
//		TaskDefendUnit*    taskDefendUnit;
//	};
//
//	enum Type
//	{
//		TASKGOTOPOINT = 0,
//		TASKPATROL = 1,
//		TASKFOLLOW = 2,
//		TASKATTACK = 3,
//		TASKWANDER = 4,
//		TASKFLEEFROMUNIT = 5,
//		TASKFLEEFROMPOINT = 6,
//		TASKDEFENDUNIT = 7
//	};
//
//	Type    m_type;
//	Content m_content;
//
//	bool Update();
//};
//
//
extern "C"
{

	inline float _vectorcall DistanceBetweenXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) noexcept
	{
		float xd = std::abs(a.x - b.x);
		float yd = std::abs(a.y - b.y);
		float d = sqrt((xd*xd) + (yd*yd));
		return d;
	}

}
Task::~Task()
{
	switch(m_type)
	{
	case Task::Type::TASKGOTOPOINT:
		if(m_content.taskGotoPoint)
		delete m_content.taskGotoPoint;
		break;
	case Task::Type::TASKPATROL:
		if (m_content.taskPatrol)
			delete m_content.taskPatrol;
		break;

	}
}
bool Task::Update()
{
	switch (m_type)
	{
	case Task::Type::TASKGOTOPOINT:
	{
		return m_content.taskGotoPoint->Update();
		break;
	}
	case Task::Type::TASKPATROL:
	{
		return m_content.taskPatrol->Update();
		break;
	}
	}
	return false;
}
//
//
//
//
//
//bool TaskGotoPoint::Update()
//{

//}
//
//bool TaskPatrol::Update()
//{
//	return false;
//}
//
//bool TaskFollow::Update()
//{
//	return false;
//}
//
//bool TaskAttack::Update()
//{
//	return false;
//}
//
//bool TaskWander::Update()
//{
//	return false;
//}
//
//bool TaskFleeFromUnit::Update()
//{
//	return false;
//}
//
//bool TaskFleeFromPoint::Update()
//{
//	return false;
//}
//
//bool TaskDefendUnit::Update()
//{
//	return false;
//}

bool TaskGotoPoint::Update()
{
	#define angle 3.14f / 8
	XMFLOAT3 position = object->GetPosition();
		if (DistanceBetweenXMFLOAT3(position, destination) > object->GetCollisionRadius())
		{
			Model* model = object->m_model;
			switch (object->GetWalkingStance())
			{
			case Unit::WalkingStance::RUN:
			{
			model->SetAnimation(SpriteModel::ModelStance::RUN);
			break;
			}
			case Unit::WalkingStance::WALK:
			{
				model->SetAnimation(SpriteModel::ModelStance::WALK);
				break;
			}
			}
			float rotation = atan2(destination.y - position.y,destination.x - position.x)*180.0f / 3.141f;
			rotation += 180.0f;
			rotation /= 22.5f;
			rotation = 20 - rotation;//to handle
			model->SetRotation((int)rotation);
			model->SetVelocity(sin(3.14F + angle * rotation)*Settings::GetAspectRatio()*object->m_speed, cos(angle*rotation)*object->m_speed*-1.0F);
			return true;
		}
		else
		{
			Model* model = object->m_model;
			model->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
			model->SetVelocity(0.0f);
			return false;
		}
}

TaskPatrol::TaskPatrol()
{
	m_target = true;
}

bool TaskPatrol::Update()
{
#define angle 3.14f / 8
	XMFLOAT3 position = object->GetPosition();
	XMFLOAT3 destination;
	switch (m_target)
	{
	case true:
		destination = pointB;
		break;
	case false:
		destination = pointA;
		break;
	}
	if (DistanceBetweenXMFLOAT3(position, destination) > object->GetCollisionRadius())
	{
		Model* model = object->m_model;
		switch (object->GetWalkingStance())
		{
		case Unit::WalkingStance::RUN:
		{
			model->SetAnimation(SpriteModel::ModelStance::RUN);
			break;
		}
		case Unit::WalkingStance::WALK:
		{
			model->SetAnimation(SpriteModel::ModelStance::WALK);
			break;
		}
		}
		float rotation = atan2(destination.y - position.y, destination.x - position.x)*180.0f / 3.141f;
		rotation += 180.0f;
		rotation /= 22.5f;
		rotation = 20 - rotation;//to handle
		model->SetRotation((int)rotation);
		model->SetVelocity(sin(3.14F + angle * rotation)*Settings::GetAspectRatio()*object->m_speed, cos(angle*rotation)*object->m_speed*-1.0F);
		return true;
	}
	else
	{
		m_target = false;
	}
}


