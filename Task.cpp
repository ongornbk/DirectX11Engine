#include "Task.h"
#include "SettingsC.h"
#include "Math.h"
#include "Unit.h"
#include <cmath>
#pragma region 

#pragma endregion

struct FLOAT3
{
	float x;
	float y;
	float z;
};

extern "C"
{

	 float _vectorcall DistanceBetweenXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) noexcept
	{
		float f[2] = { (a.x - b.x),(a.y - b.y) };
		return sqrt((f[0]*f[0]) + (f[1]*f[1]));
	}

	 FLOAT3 _vectorcall calculateVelocity(float speed,float rotation) noexcept
	{
#define ANGLE (3.14f / 8.0f)
		 FLOAT3 f3;
		f3.x = sin(3.14f + ANGLE * rotation)*Settings::GetAspectRatio()*speed;
		f3.y = cos(ANGLE*rotation)*speed * -1.0f;
		f3.z = 0.0f;
		return f3;
	}

}







TaskGotoPoint::TaskGotoPoint()
{
	m_type = Type::TASKGOTOPOINT;
	
}

bool TaskGotoPoint::Update()
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
	XMFLOAT3 position = object->GetPosition();

	if (object->m_collided)
	{
		object->SetAnimation(Unit::ModelStance::MS_TOWNNEUTRAL);
		object->SetVelocity(0.0f, 0.0f, 0.0f);
		return false;
	}

	
	
	else
	{
		
		if (DistanceBetweenXMFLOAT3(position, destination) > object->GetCollisionRadius())
		{
			float rotation = atan2(destination.y - position.y, destination.x - position.x)*180.0f / XM_PI;
			rotation += 180.0f;
			rotation /= 22.5f;
			rotation = 20 - rotation;
			object->SetRotation(rotation);
			FLOAT3 f3 = calculateVelocity(object->m_speed[0], rotation);
			object->SetVelocity(f3.x, f3.y, f3.z);
			return true;

		}
		else
		{
			object->SetAnimation(Unit::ModelStance::MS_TOWNNEUTRAL);
			object->SetVelocity(0.0f,0.0f,0.0f);
			return false;
		}
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
		object->SetRotation((int)rotation);
		FLOAT3 f3 = calculateVelocity(object->m_speed[0], rotation);
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
}

bool TaskFollow::Update()
{
#define angle 3.14f / 8
	XMFLOAT3 position = object->GetPosition();
	XMFLOAT3 destination = target->GetPosition();
	if (DistanceBetweenXMFLOAT3(position, destination) > 200.0f)
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
		object->SetRotation((int)rotation);
		FLOAT3 f3 = calculateVelocity(object->m_speed[0], rotation);
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
