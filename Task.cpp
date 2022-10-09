#include "Task.h"
#include "SettingsC.h"
#include "modern/modern.h"
#include "Unit.h"
#include <cmath>

#include "IPP.h"
#include "UserInterfaceGame.h"


#define CONTINUE_TASK return true
#define CLOSE_TASK return false

//Do not lock owner of task
	 

	 DirectX::XMFLOAT3 _vectorcall calculateVelocity(const float speed,const float rotation,const float rotations) modern_except_state
	{
		const float angle = (3.14f * 2.f) / rotations;
		DirectX::XMFLOAT3 f3;
		f3.x = sin(3.14f + angle * rotation)*Settings::GetAspectRatio()*speed;
		f3.y = cos(angle*rotation)*speed * -1.0f;
		f3.z = 0.0f;
		return f3;
	}

	 DirectX::XMFLOAT3 _vectorcall calculateVelocity(const float speed, const float rotation) modern_except_state
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
	class Unit* const A = (class Unit*)object.get();
	
	if (A)
	{
		//modern_guard guard(A);
		XMFLOAT3 position = A->GetPosition();



		if (modern_xfloat3_distance2(position, destination) > A->GetCollisionRadius())
		{

			switch (A->GetWalkingStance())
			{
			case WalkingStance::WALKING_STANCE_RUN:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_RUN);
				break;
			}
			case WalkingStance::WALKING_STANCE_WALK:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_WALK);
				break;
			}
			}
			A->m_rad_rotation = atan2(destination.y - position.y, destination.x - position.x);
			float rotation = modern_xangle2_between_points3(position, destination);

			rotation += 180.f;
			rotation /= (360.f / A->GetNumberOfRotations());
			XMFLOAT3 f3 = calculateVelocity(A->m_speed[0], fmod(rotation + (A->GetNumberOfRotations() / 2.f), A->GetNumberOfRotations()), A->GetNumberOfRotations());
			A->SetRotation(rotation + (A->GetNumberOfRotations() / 2.f));
			A->SetVelocity(f3.x, f3.y, f3.z);

			//UserInterfaceGame::GetGameChat()->PushText(modern_string((int32_t)rotation).c_str());

			CONTINUE_TASK;
		}
		else
		{
			CLOSE_TASK;
		}
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
	class Unit* const A = (class Unit*)object.get();


#define angle 3.14f / 8
	if (A)
	{
		//modern_guard guard(A);
		DirectX::XMFLOAT3 position = A->GetPosition();
		DirectX::XMFLOAT3 destination;
		switch (m_target)
		{
		case true:
			destination = pointB;
			break;
		case false:
			destination = pointA;
			break;
		}
		if (modern_xfloat3_distance2(position, destination) > A->GetCollisionRadius())
		{
			switch (A->GetWalkingStance())
			{
			case WalkingStance::WALKING_STANCE_RUN:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_RUN);
				break;
			}
			case WalkingStance::WALKING_STANCE_WALK:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_WALK);
				break;
			}
			}
			A->m_rad_rotation = atan2(destination.y - position.y, destination.x - position.x);
			float rotation = atan2(destination.y - position.y, destination.x - position.x) * 180.0f / 3.141f;
			rotation += 90.0f;
			rotation /= (360.f / A->GetNumberOfRotations());
			rotation = A->GetNumberOfRotations() - rotation;
			A->SetRotation(rotation);
			XMFLOAT3 f3 = calculateVelocity(A->m_speed[0], A->GetRotation());
			A->SetVelocity(f3.x, f3.y, f3.z);
			CONTINUE_TASK;
		}
		else
		{
			m_target = false;
		}
	}
	else
	{
		CLOSE_TASK;
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
	class Unit* const A = (class Unit*)object.get();
	class Unit* const B = (class Unit*)target.get();
#define angle 3.14f / 8
	if (A&&B)
	{
		//modern_guard guardA(A);
		modern_shared_guard guardB(B);

		DirectX::XMFLOAT3 position = A->GetPosition();
		DirectX::XMFLOAT3 destination = B->GetPosition();
		if (modern_xfloat3_distance2(position, destination) > 200.0f)
		{
			switch (A->GetWalkingStance())
			{
			case WalkingStance::WALKING_STANCE_RUN:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_RUN);
					break;
			}
			case WalkingStance::WALKING_STANCE_WALK:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_WALK);
				break;
			}
			}
			A->m_rad_rotation = atan2(destination.y - position.y, destination.x - position.x);
			float rotation = atan2(destination.y - position.y, destination.x - position.x) * 180.0f / 3.141f;
			rotation += 90.f;
			rotation /= (360.f / A->GetNumberOfRotations());
			rotation = A->GetNumberOfRotations() - rotation;
			A->SetRotation(rotation);
			XMFLOAT3 f3 = calculateVelocity(A->m_speed[0], A->GetRotation());
			A->SetVelocity(f3.x, f3.y, f3.z);
			CONTINUE_TASK;
		}
		else
		{
			A->SetAnimation(ModelStance::MODEL_STANCE_TOWNNEUTRAL);
			A->SetVelocity(0.0f, 0.0f, 0.0f);
		}
}
else
{
CLOSE_TASK;
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
	class Unit* const A = (class Unit*)object.get();
	class Unit* const B = (class Unit*)target.get();
	if(A&&B)
	{
		modern_shared_guard guardA(A);
		modern_shared_guard guardB(B);
		const DirectX::XMFLOAT3 position = A->GetPosition();
		const DirectX::XMFLOAT3 destination = B->m_boundingSphere.Center;

		const Attack atk = A->GetAttack();

		inrange = (modern_xfloat3_distance2(position, destination) > atk.range);
	}
}

bool TaskAttack::Update()
{
	class Unit* const A = (class Unit*)object.get();
	class Unit* const B = (class Unit*)target.get();


	if (A && B)
	{
		//modern_guard guardA(A);//Maybe Already Guarded
		modern_shared_guard guardB(B);

		DirectX::XMFLOAT3 position = A->GetPosition();
		DirectX::XMFLOAT3 destination = B->GetPosition();

		const Attack atk = A->GetAttack();

		inrange = (modern_xfloat3_distance2(position, destination) > atk.range);


		if (inrange)
		{
			atk.active = false;
			//float rotation = modern_atan2(destination.y - position.y, destination.x - position.x);
			//rotation += 90.f;
			//rotation /= (360.f / A->GetNumberOfRotations());
			//rotation = A->GetNumberOfRotations() - rotation;
			//A->SetRotation(rotation);

			float rotation = modern_xangle2_between_points3(position, destination);

			rotation += 180.f;
			rotation /= (360.f / A->GetNumberOfRotations());
			XMFLOAT3 f3 = calculateVelocity(A->m_speed[0], fmod(rotation + (A->GetNumberOfRotations() / 2.f), A->GetNumberOfRotations()), A->GetNumberOfRotations());
			A->SetRotation(rotation + (A->GetNumberOfRotations() / 2.f));
			A->SetVelocity(f3.x, f3.y, f3.z);

			switch (A->GetWalkingStance())
			{
			case WalkingStance::WALKING_STANCE_RUN:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_RUN);
				break;
			}
			case WalkingStance::WALKING_STANCE_WALK:
			{
				A->SetAnimation(ModelStance::MODEL_STANCE_WALK);
				break;
			}
			}

			//DirectX::XMFLOAT3 f3 = calculateVelocity(A->m_speed[0], A->GetRotation());
			//A->SetVelocity(f3.x, f3.y, f3.z);
			CONTINUE_TASK;
		}
		else
		{
			return A->BeginAttack(B);
		}
	}
	{
		CLOSE_TASK;
	}
	CLOSE_TASK;
}

void TaskAttack::Release()
{
	class Unit* const A = (class Unit*)object.get();
	if (A)
	{
		//modern_guard guardA(A);
		const Attack atk = A->GetAttack();
		atk.active = false;
	}
	delete this;
}
