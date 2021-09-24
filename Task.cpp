#include "Task.h"
#include "SettingsC.h"
#include "modern/modern.h"
#include "Unit.h"
#include <cmath>

#include "IPP.h"
#include "UserInterfaceGame.h"

#define CONTINUE_TASK return true
#define CLOSE_TASK return false
	 

	 DirectX::XMFLOAT3 _vectorcall calculateVelocity(const float speed,const float rotation,const float rotations) noexcept
	{
		const float angle = (3.14f * 2.f) / rotations;
		DirectX::XMFLOAT3 f3;
		f3.x = sin(3.14f + angle * rotation)*Settings::GetAspectRatio()*speed;
		f3.y = cos(angle*rotation)*speed * -1.0f;
		f3.z = 0.0f;
		return f3;
	}

	 DirectX::XMFLOAT3 _vectorcall calculateVelocity(const float speed, const float rotation) noexcept
	 {
		 const float angle = 3.14f / 8.f;
		 DirectX::XMFLOAT3 f3;
		 f3.x = sin(3.14f + angle * rotation) * Settings::GetAspectRatio() * speed;
		 f3.y = cos(angle * rotation) * speed * -1.0f;
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


		
		if (modern_xfloat3_distance2(position, destination) > object->GetCollisionRadius())
		{

			switch (object->GetWalkingStance())
			{
			case WalkingStance::WALKING_STANCE_RUN:
			{
				object->SetAnimation(ModelStance::MODEL_STANCE_RUN);
				break;
			}
			case WalkingStance::WALKING_STANCE_WALK:
			{
				object->SetAnimation(ModelStance::MODEL_STANCE_WALK);
				break;
			}
			}

			float rotation = modern_xangle2_between_points3(position,destination);
		
			rotation += 180.f;
			rotation /= (360.f / object->GetNumberOfRotations());
			XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], fmod(rotation + (object->GetNumberOfRotations() / 2.f), object->GetNumberOfRotations()), object->GetNumberOfRotations());
			object->SetRotation(rotation + (object->GetNumberOfRotations() / 2.f));
			object->SetVelocity(f3.x, f3.y, f3.z);
			
			//UserInterfaceGame::GetGameChat()->PushText(modern_string((int32_t)rotation).c_str());

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
	if (modern_xfloat3_distance2(position, destination) > object->GetCollisionRadius())
	{
		switch (object->GetWalkingStance())
		{
		case WalkingStance::WALKING_STANCE_RUN:
		{
			object->SetAnimation(ModelStance::MODEL_STANCE_RUN);
			break;
		}
		case WalkingStance::WALKING_STANCE_WALK:
		{
			object->SetAnimation(ModelStance::MODEL_STANCE_WALK);
			break;
		}
		}
		float rotation = atan2(destination.y - position.y, destination.x - position.x)*180.0f / 3.141f;
		rotation += 90.0f;
		rotation /= (360.f / object->GetNumberOfRotations());
		rotation = object->GetNumberOfRotations() - rotation;
		object->SetRotation(rotation);
		XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], object->GetRotation());
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
	if (modern_xfloat3_distance2(position, destination) > 200.0f)
	{
		switch (object->GetWalkingStance())
		{
		case WalkingStance::WALKING_STANCE_RUN:
		{
			object->SetAnimation(ModelStance::MODEL_STANCE_RUN);
			break;
		}
		case WalkingStance::WALKING_STANCE_WALK:
		{
			object->SetAnimation(ModelStance::MODEL_STANCE_WALK);
			break;
		}
		}
		float rotation = atan2(destination.y - position.y, destination.x - position.x)*180.0f / 3.141f;
		rotation += 90.f;
		rotation /= (360.f / object->GetNumberOfRotations());
		rotation = object->GetNumberOfRotations() - rotation;
		object->SetRotation(rotation);
		XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], object->GetRotation());
		object->SetVelocity(f3.x, f3.y, f3.z);
		CONTINUE_TASK;
	}
	else
	{
		object->SetAnimation(ModelStance::MODEL_STANCE_TOWNNEUTRAL);
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

		inrange = (modern_xfloat3_distance2(position, destination) > atk.range);
	}
}

bool TaskAttack::Update()
{
	DirectX::XMFLOAT3 position = object->GetPosition();
	DirectX::XMFLOAT3 destination = target->GetPosition();
	
	const Attack atk = object->GetAttack();

	inrange = (modern_xfloat3_distance2(position, destination) > atk.range);

	
	if (inrange)
	{
		atk.active = false;
		float rotation = atan2(destination.y - position.y, destination.x - position.x) * 180.0f / 3.141f;
		rotation += 90.0f;
		rotation /= (360.f / object->GetNumberOfRotations());
		rotation = object->GetNumberOfRotations() - rotation;
		object->SetRotation(rotation);
		switch (object->GetWalkingStance())
		{
		case WalkingStance::WALKING_STANCE_RUN:
		{
			object->SetAnimation(ModelStance::MODEL_STANCE_RUN);
			break;
		}
		case WalkingStance::WALKING_STANCE_WALK:
		{
			object->SetAnimation(ModelStance::MODEL_STANCE_WALK);
			break;
		}
		}
		
		DirectX::XMFLOAT3 f3 = calculateVelocity(object->m_speed[0], object->GetRotation());
		object->SetVelocity(f3.x, f3.y, f3.z);
		CONTINUE_TASK;
	}
	else
	{
		return object->BeginAttack(target);
	}
	CLOSE_TASK;
}

void TaskAttack::Release()
{
	const Attack atk = object->GetAttack();
	atk.active = false;
	delete this;
}
