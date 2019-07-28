#include "Task.h"
#include "SettingsC.h"
#include "Math.h"
#include "Unit.h"
#include <cmath>



	 

	 XMFLOAT3 _vectorcall calculateVelocity(const float speed,const float rotation) noexcept
	{
#define ANGLE (3.14f / 8.0f)
		 XMFLOAT3 f3;
		f3.x = sin(3.14f + ANGLE * rotation)*Settings::GetAspectRatio()*speed;
		f3.y = cos(ANGLE*rotation)*speed * -1.0f;
		f3.z = 0.0f;
		return f3;
	}


TaskGotoPoint::TaskGotoPoint()
{
	m_type = Type::TASKGOTOPOINT;
	m_stance = TSRUNNING;
}

bool TaskGotoPoint::Update()
{

	
	XMFLOAT3 position = object->GetPosition();


		
		if (XMFloat3Distance2D(position, destination) > object->GetCollisionRadius())
		{

			switch (object->GetWalkingStance())
			{
			case Unit::WalkingStance::WS_RUN:
			{
				object->SetAnimation(Unit::ModelStance::MS_RUN);
				break;
			}
			case Unit::WalkingStance::WS_WALK:
			{
				object->SetAnimation(Unit::ModelStance::MS_WALK);
				break;
			}
			}

			float rotation = atan2(destination.y - position.y, destination.x - position.x)*180.0f / XM_PI;
			rotation += 180.0f;
			rotation /= 22.5f;
			rotation = 20 - rotation;
			object->SetRotation(rotation);
			XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], rotation);
			object->SetVelocity(f3.x, f3.y, f3.z);
			return true;
		}
		else
		{
			return false;
		}
}

void TaskGotoPoint::Release()
{
	delete this;
}

TaskPatrol::TaskPatrol()
{
	m_target = true;
	m_type = Type::TASKPATROL;
	m_stance = TSRUNNING;
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
	if (XMFloat3Distance2D(position, destination) > object->GetCollisionRadius())
	{
		switch (object->GetWalkingStance())
		{
		case Unit::WalkingStance::WS_RUN:
		{
			object->SetAnimation(Unit::ModelStance::MS_RUN);
			break;
		}
		case Unit::WalkingStance::WS_WALK:
		{
			object->SetAnimation(Unit::ModelStance::MS_WALK);
			break;
		}
		}
		float rotation = atan2(destination.y - position.y, destination.x - position.x)*180.0f / 3.141f;
		rotation += 180.0f;
		rotation /= 22.5f;
		rotation = 20 - rotation;
		object->SetRotation(rotation);
		XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], rotation);
		object->SetVelocity(f3.x, f3.y, f3.z);
		return true;
	}
	else
	{
		m_target = false;
	}
	return false;
}

void TaskPatrol::Release()
{
	delete this;
}

TaskFollow::TaskFollow()
{
	m_type = Type::TASKFOLLOW;
	m_stance = TSRUNNING;
}

bool TaskFollow::Update()
{
#define angle 3.14f / 8
	XMFLOAT3 position = object->GetPosition();
	XMFLOAT3 destination = target->GetPosition();
	if (XMFloat3Distance2D(position, destination) > 200.0f)
	{
		switch (object->GetWalkingStance())
		{
		case Unit::WalkingStance::WS_RUN:
		{
			object->SetAnimation(Unit::ModelStance::MS_RUN);
			break;
		}
		case Unit::WalkingStance::WS_WALK:
		{
			object->SetAnimation(Unit::ModelStance::MS_WALK);
			break;
		}
		}
		float rotation = atan2(destination.y - position.y, destination.x - position.x)*180.0f / 3.141f;
		rotation += 180.0f;
		rotation /= 22.5f;
		rotation = 20 - rotation;
		object->SetRotation(rotation);
		XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], rotation);
		object->SetVelocity(f3.x, f3.y, f3.z);
		return true;
	}
	else
	{
		object->SetAnimation(Unit::ModelStance::MS_TOWNNEUTRAL);
		object->SetVelocity(0.0f,0.0f,0.0f);
	}
	return false;
}

void TaskFollow::Release()
{
	delete this;
}
