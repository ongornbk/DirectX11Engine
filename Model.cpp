#include "Model.h"
#include "Timer.h"
#include "Engine.h"
#include "GlobalUtilities.h"

#pragma region
#define XMFLOAT3ZERO XMFLOAT3(POSITION_ZERO_POINT_X, POSITION_ZERO_POINT_Y, POSITION_ZERO_POINT_Z)
#define UPDATEWORLD  XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity())
#define STOREFLOAT   XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(
#define DEND         ));
#pragma endregion

namespace
{
	static float m_lastsize = 0.0f;
}

Model::Model() : BoundingSphere()
{
	m_velocity         = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_lastPosition     = XMFLOAT3ZERO;
	Center             = XMFLOAT3ZERO;
	Radius             = COLLISION_DISABLED_OR_NULL;
	m_spriteModel      = NULL;
	m_flags[0]         = TRUE;//rendering
	m_flags[1]         = FALSE;//selected
	m_flags[2]         = TRUE;//pushable
	m_flags[3]         = FALSE;//blocked
	UPDATEWORLD;
}

Model::Model(const Model &model) : BoundingSphere()
{
	*this = model;
}

Model::~Model(void)
{
	if (m_spriteModel)
	{
		delete m_spriteModel;
		m_spriteModel = NULL;
	}

}



void Model::InitializeSpriteModel(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader,ModelPaths paths, float spriteSize)
{
	m_spriteModel = new SpriteModel(spriteSize);
	dynamic_cast<SpriteModel*>(m_spriteModel)->Initialize(device, deviceContext, shader,paths);
	m_lastsize = spriteSize;
}





void Model::Update(float dt)
{
	if (!m_flags[3])
	{
		if (!m_spriteModel->IsLocked())
		{
			m_lastPosition = Center;
			if (XMVectorGetIntX < 0)
			{
				Center.x -= m_velocity.x * dt;
				Center.y -= m_velocity.y * dt;
				//	Center.z -= m_velocity.z * dt;

			}
			else
			{
				Center.x += m_velocity.x * dt;
				Center.y += m_velocity.y * dt;
				//Center.z += m_velocity.z * dt;
			}
		}

		if (m_spriteModel&&m_flags[0])
		{
			STOREFLOAT Center.x, Center.y, Center.z DEND
			m_spriteModel->Update(dt);
		}
	}
}

void Model::UpdatePosition()
{
	//m_lastPosition = Center;
	//XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y, Center.z));
	//if (m_spriteModel)
	//{
	//	m_spriteModel->Update();
	//}
}

void Model::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,Shader* shader)
{
	if (m_spriteModel&&m_flags[0])
	{
		m_spriteModel->Render(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix,shader);
	}
}

void Model::Resize(ID3D11Device * device, Shader * shader, float resize)
{
	m_spriteModel->Resize(device,shader,resize);
}

void Model::SetRenderingStance(bool render)
{
	this->m_flags[0] = render;
}

void Model::Block(bool block)
{
	m_flags[3] = block;
}

XMFLOAT3 Model::GetPosition()
{
	return Center;
}

XMFLOAT3 Model::GetVelocity()
{
	return m_velocity;
}

void Model::GoBack()
{
	Center = m_lastPosition;
	//XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y, Center.z));
	//if (m_spriteModel)
	//{
	//	m_spriteModel->Update();
	//}
}

void Model::SetCollisionRadius(float radius)
{
	this->Radius = radius;
}

void Model::SetPosition(float x, float y,float z)
{
	Center.x = x;
	Center.y =-= (m_lastsize/2.0f);
	Center.z = z;
}

void Model::SetPosition(XMFLOAT3 position)
{
	Center = position;
}

void Model::SetVelocity(float x, float y,float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

void Model::SetVelocity(XMFLOAT3 velocity)
{
	m_velocity = velocity;
}

void Model::Translate(float x, float y,float z)
{
	Center.x += x;
	Center.y += y;
	Center.z += z;
}

void Model::SetRotation(int rotation)
{
	m_spriteModel->SetRotation(rotation);
}

void Model::SetAnimation(SpriteModel::ModelStance animation,bool lock,bool force)
{
	m_spriteModel->SetAnimation(animation,lock,force);

}

void Model::SetAnimationSpeed(float speed)
{
}

void Model::PlayAnimation(SpriteModel::ModelStance animation)
{
	m_spriteModel->PlayAnimation(animation);
}

void Model::PlayAnimation(SpriteModel::ModelStance animation, SpriteModel::ModelStance after)
{
	m_spriteModel->SetAnimation(after, false, false);
	m_spriteModel->PlayAnimation(animation);
}



