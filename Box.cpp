#include "Box.h"



Box::Box(DXVECTOR position,DXVECTOR rotation,DXVECTOR scale)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
}


Box::~Box()
{
}

void Box::Update(float dt)
{
	m_rotation.x += dt;
	m_rotation.y += dt;
	m_rotation.z += dt;
}

void Box::SetPosition(float x,float y,float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
