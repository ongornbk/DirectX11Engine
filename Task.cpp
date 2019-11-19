#include "Task.h"
#include "SettingsC.h"
#include "Math.h"
#include "Unit.h"
#include <cmath>


#define CONTINUE_TASK return true
#define CLOSE_TASK return false
	 

	 DirectX::XMFLOAT3 _vectorcall calculateVelocity(const float speed,const float rotation) noexcept
	{
#define ANGLE (3.14f / 8.0f)
		 DirectX::XMFLOAT3 f3;
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
			CONTINUE_TASK;
		}
		else
		{
			CLOSE_TASK;
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
		CONTINUE_TASK;
	}
	else
	{
		m_target = false;
	}
	CLOSE_TASK;
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
		CONTINUE_TASK;
	}
	else
	{
		object->SetAnimation(Unit::ModelStance::MS_TOWNNEUTRAL);
		object->SetVelocity(0.0f,0.0f,0.0f);
	}
	CLOSE_TASK;
}

void TaskFollow::Release()
{
	delete this;
}

TaskAttack::TaskAttack()
{
	m_type = Type::TASKATTACK;
	m_stance = TSRUNNING;

	
}

void TaskAttack::Initialize()
{
	if(object&&target)
	{
		const DirectX::XMFLOAT3 position = object->GetPosition();
		const DirectX::XMFLOAT3 destination = target->m_boundingSphere.Center;

		const Attack atk = object->GetAttack();

		inrange = (XMFloat3Distance2D(position, destination) > atk.range);
	}
}

bool TaskAttack::Update()
{
	DirectX::XMFLOAT3 position = object->GetPosition();
	DirectX::XMFLOAT3 destination = target->m_boundingSphere.Center;
	
	const Attack atk = object->GetAttack();

	if (XMFloat3Distance2D(position, destination) > atk.range)
		inrange = true;
	else inrange = false;
	
	if (inrange)
	{
		atk.active = false;
		float rotation = atan2(destination.y - position.y, destination.x - position.x) * 180.0f / 3.141f;
		rotation += 180.0f;
		rotation /= 22.5f;
		rotation = 20 - rotation;
		object->SetRotation(rotation);
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
		
		DirectX::XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], rotation);
		object->SetVelocity(f3.x, f3.y, f3.z);
		CONTINUE_TASK;
	}
	else
	{
		return object->Attack(target);
	}
	CLOSE_TASK;
}

void TaskAttack::Release()
{
	const Attack atk = object->GetAttack();
	atk.active = false;
	delete this;
}
