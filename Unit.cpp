#include "Unit.h"



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

void Unit::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, ModelPaths paths, float modelsize,float collision,XMFLOAT3 position,bool wander)
{
	m_model = new Model();
	m_model->InitializeSpriteModel(device, deviceContext, shader, paths, modelsize);
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
	return m_speed;
}

void Unit::SetSpeed(float speed)
{
	m_speed = speed;
}

Unit::WalkingStance Unit::GetWalkingStance()
{
	return m_walkingStance;
}

void Unit::SetWalkingStance(WalkingStance stance)
{
	this->m_walkingStance = stance;
}
