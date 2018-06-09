#include "Unit.h"
#include "Engine.h"
#include "S_ModelPaths.h"

Unit::Unit()
{
	m_model = new Model();

}


Unit::~Unit()
{
	if (m_model)
	{
		delete m_model;
		m_model = NULL;
	}
}

void Unit::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR* paths, float modelsize,float collision,XMFLOAT3 position,bool wander)
{

	m_model = new Model();
	wstring tmp0 = wstring(paths);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	ModelPaths* ptr = S_ModelPaths::GetModelPaths(tmp1);
	m_model->InitializeSpriteModel(device, deviceContext, shader, ptr, modelsize);
	m_model->Radius = collision;
	m_model->Center = position;
	m_wanderingFlag = wander;
}



void Unit::Update()
{
	if (!m_tasks.Update())

	{
		if(m_wanderingFlag)m_tasks.Wander(this);
	}
	else
	{

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

Model * Unit::GetModel()
{
	return m_model;
}

XMFLOAT3 Unit::GetPoint()
{
	return m_model->Center;
}

float Unit::GetCollisionRadius()
{
	return m_model->Radius;
}

XMFLOAT3 Unit::GetPosition()
{
	return m_model->Center;
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
	m_model->SetRotations(rotations);
}

void Unit::DiscardTasks()
{
	m_tasks.Discard();
}
