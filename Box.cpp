#include "Box.h"



Box::Box(XMVECTOR position,XMVECTOR rotation,XMVECTOR scale)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
}


Box::~Box()
{
	if (m_vertexBuffer)
	{
		(void)m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
	if (m_indexBuffer)
	{
		(void)m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}
}

void Box::Initialize(ID3D11Device * device)
{
}

void Box::Update(float dt)
{
	m_rotation.m128_f32[0] += dt;
	m_rotation.m128_f32[1] += dt;
	m_rotation.m128_f32[2] += dt;
}

void Box::Draw(ID3D11Device * device)
{
}

void Box::Release()
{
}

void Box::SetPosition(float x,float y,float z)
{
	m_position.m128_f32[0] = x;
	m_position.m128_f32[1] = y;
	m_position.m128_f32[2] = z;
}
