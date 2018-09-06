#include "Unit.h"
#include "Engine.h"
#include "S_ModelPaths.h"
#include "RendererManager.h"
#include "Onion.h"

Unit::Unit() : Model()
{
}


Unit::~Unit()
{
}

void Unit::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR* paths, float modelsize, float collision, XMFLOAT3 position, bool wander)
{
	wstring tmp0 = wstring(paths);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	ModelPaths* ptr = S_ModelPaths::GetModelPaths(tmp1);
	Model::InitializeSpriteModel(device, deviceContext, shader, ptr, modelsize);
	Model::Radius = collision;
	Model::Center = position;
	Model::Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	Model::Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	m_wanderingFlag = wander;
}



void Unit::Update(float dt)
{
	if (!m_tasks.Update())if(m_wanderingFlag)m_tasks.Wander(this);

	Model::Update(dt);

	Model::SetRenderingStance(validateRendering(Model::Center));

	int16_t mousePosition[2];
	UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
	FXMVECTOR point = XMVectorSet((float)mousePosition[0], (float)mousePosition[1], 0.0f, 0.0f);
	if (Model::BoundingSphere::Contains(point))
	{
		Model::GoBack();
		if (Model::BoundingSphere::Contains(point))
		{
			Model::m_flags[4] = true;
			Model::m_flags[1] = true;
			GLOBAL m_lastSelectedUnit = this;
		}
		else
		{
			Model::m_flags[4] = false;
			Model::m_flags[1] = false;
		}
	}
	else
	{
		Model::m_flags[4] = false;
		Model::m_flags[1] = false;
	}
	if (TileMap::CollisionAt(Model::Center))
	{
		Model::GoBack();
		if (TileMap::CollisionAt(Model::Center))
		{
			Model::m_flags[4] = true;
			Model::m_flags[1] = true;
		}
		else
		{
			Model::m_flags[4] = false;
			Model::m_flags[1] = false;
		}
	}
	else
	{
		Model::m_flags[4] = false;
		Model::m_flags[1] = false;
	}
	
}

void Unit::SetTask(Task* task)
{
	m_tasks.SetTask(task);
}

void Unit::GiveTask(Task * task)
{
	m_tasks.QueueTask(task);
}





float Unit::GetCollisionRadius()
{
	return Model::Radius;
}

XMFLOAT3 Unit::GetPosition()
{
	return Model::Center;
}

float Unit::GetSpeed()
{
	return m_speed[0];
}

void Unit::SetSpeed(float speed)
{
	m_speed[0] = speed;
	m_speed[1] = speed;
}

Unit::WalkingStance Unit::GetWalkingStance()
{
	return m_walkingStance;
}

void Unit::SetWalkingStance(WalkingStance stance)
{
	this->m_walkingStance = stance;
	switch (stance)
	{
	case WALK:
		m_speed[0] = m_speed[1] / 2.0f;
		break;
	case RUN: 
		m_speed[0] = m_speed[1];
		break;
	}
}

void Unit::ChangeWalkingStance()
{
	switch (m_walkingStance)
	{
	case Unit::WalkingStance::RUN:
			m_walkingStance = Unit::WalkingStance::WALK;
			m_speed[0] = m_speed[1] / 2.0f;
			break;
	case Unit::WalkingStance::WALK:
		m_walkingStance = Unit::WalkingStance::RUN;
		m_speed[0] = m_speed[1];
		break;
	}
}

void Unit::SetRotations(float rotations)
{
	Model::SetRotations(rotations);
}

void Unit::DiscardTasks()
{
	m_tasks.Discard();
}

void Unit::SetPosition(XMFLOAT3 position)
{
	Model::Center = position;
}



