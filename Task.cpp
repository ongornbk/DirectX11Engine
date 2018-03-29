#include "Task.h"
#include "SettingsC.h"
#include <cmath>
#include "Unit.h"

#pragma region 

#pragma endregion
//

//
//struct TaskAttack
//{
//	bool          Update();
//	Unit*         object;
//	atomic<Unit*> target;
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
namespace
{
#pragma region
#define ANGLE 3.14f / 8.0f
	using std::abs;
#pragma endregion
	template <class T> inline void SafeDelete(T* type)
	{
		if (T) delete T;
	}

	extern "C"
	{

		inline float _vectorcall DistanceBetweenXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) noexcept
		{
			float xd = abs(a.x - b.x);
			float yd = abs(a.y - b.y);
			float d = sqrt((xd*xd) + (yd*yd));
			return d;
		}

		inline void _vectorcall ToRotation(float &value, float rotation) noexcept
		{
			value += 180.0f;
			value /= 22.5f;
			value = (20 - value);
		}

		inline float _vectorcall Angle2BetweenPoints(XMFLOAT3 a, XMFLOAT3 b) noexcept
		{
			return (atan2(a.y - b.y, a.x - b.x)*180.0f / 3.141f);
		}

		inline float _vectorcall CalculateVelocity(float rotation, float speed) noexcept
		{
			return sin(3.14F + ANGLE * rotation)*Settings::GetAspectRatio()*speed, cos(ANGLE*rotation)*speed*-1.0F;
		}

	}


}
Task::~Task()
{
	switch(m_type)
	{
	case Task::Type::TASKGOTOPOINT:
	{
		//if(m_content.taskGotoPoint)
		//delete m_content.taskGotoPoint;
		SafeDelete(m_content.taskGotoPoint);
		break;
	}
	case Task::Type::TASKPATROL:
	{
		//if (m_content.taskPatrol)
			//delete m_content.taskPatrol;
		SafeDelete(m_content.taskPatrol);
		break;
	}
		case Task::Type::TASKFOLLOW:
		{
		//if (m_content.taskFollow) delete m_content.taskFollow;
			SafeDelete(m_content.taskFollow);
		break;
	}
		case Task::Type::TASKFLEEFROMPOINT:
		{
			//if (m_content.taskFollow) delete m_content.taskFollow;
			SafeDelete(m_content.taskFleeFromPoint);
			break;
		}
		case Task::Type::TASKFLEEFROMUNIT:
		{
			//if (m_content.taskFollow) delete m_content.taskFollow;
			SafeDelete(m_content.taskFleeFromUnit);
			break;
		}

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
		case Task::Type::TASKFOLLOW:
	{
		return m_content.taskFollow->Update();
		break;
	}
		case Task::Type::TASKFLEEFROMPOINT:
		{
			return m_content.taskFleeFromPoint->Update();
			break;
		}
		case Task::Type::TASKFLEEFROMUNIT:
		{
			return m_content.taskFleeFromUnit->Update();
			break;
		}
	}
	return false;
}






bool TaskGotoPoint::Update()
{

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
			float rotation = Angle2BetweenPoints(destination, position);
			ToRotation(rotation,20.0f);
			model->SetRotation((int)rotation);
			model->SetVelocity(CalculateVelocity(rotation,object->m_speed));
			return true;
		}
		else
		{
			Model* model = object->m_model;
			model->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
			model->SetVelocity();
			return false;
		}
}

TaskPatrol::TaskPatrol()
{
	m_target = true;
}

bool TaskPatrol::Update()
{
	XMFLOAT3 position = object->GetPosition();
	XMFLOAT3 destination;
	switch (m_target)
	{
	case true:
		destination = pointB;
		m_target = false;
		break;
	case false:
		destination = pointA;
		m_target = true;
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
		float rotation = Angle2BetweenPoints(destination, position);
		ToRotation(rotation, 20.0f);
		model->SetRotation((int)rotation);
		model->SetVelocity(CalculateVelocity(rotation, object->m_speed));
		return true;
	}
}

bool TaskFollow::Update()
{
	XMFLOAT3 position = object->GetPosition();
	XMFLOAT3 destination = target.load()->GetPosition();
	if (DistanceBetweenXMFLOAT3(position, destination) > 200.0f)
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
		float rotation = Angle2BetweenPoints(destination, position);
		ToRotation(rotation, 20.0f);
		model->SetRotation((int)rotation);
		model->SetVelocity(CalculateVelocity(rotation, object->m_speed));
		return true;
	}
	else
	{
		Model* model = object->m_model;
		model->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
		model->SetVelocity();
	}
}

bool TaskFleeFromPoint::Update()
{

	XMFLOAT3 position = object->GetPosition();
	if (DistanceBetweenXMFLOAT3(position, pointA) < 600.0f)
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
		float rotation = Angle2BetweenPoints(pointA, position);
		ToRotation(rotation, 28.0f);
		model->SetRotation((int)rotation);
		model->SetVelocity(CalculateVelocity(rotation, object->m_speed));
		return true;
	}
	else
	{
		Model* model = object->m_model;
		model->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
		model->SetVelocity();
		return false;
	}
}

bool TaskFleeFromUnit::Update()
{
	XMFLOAT3 position = object->GetPosition();
	XMFLOAT3 pointA = target.load()->GetPosition();
	if (DistanceBetweenXMFLOAT3(position, pointA) < 600.0f)
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
		float rotation = Angle2BetweenPoints(pointA, position);
		ToRotation(rotation, 28.0f);
		model->SetRotation((int)rotation);
		model->SetVelocity(CalculateVelocity(rotation, object->m_speed));
		return true;
	}
	else
	{
		Model* model = object->m_model;
		model->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
		model->SetVelocity();
		return false;
	}
}
