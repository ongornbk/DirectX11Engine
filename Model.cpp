#include "Model.h"
#include "IPP.h"
#include "Engine.h"
#include "GlobalUtilities.h"

namespace
{
	static float m_lastsize = 0.0f;
}

Model::Model() : BoundingSphere()
{
	m_floats[0]        = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_floats[1]        = XMFLOAT3(POSITION_ZERO_POINT_X, POSITION_ZERO_POINT_Y, POSITION_ZERO_POINT_Z);
	Center             = XMFLOAT3(POSITION_ZERO_POINT_X, POSITION_ZERO_POINT_Y, POSITION_ZERO_POINT_Z);
	Radius             = COLLISION_DISABLED_OR_NULL;
	m_spriteModel      = NULL;
	m_flags[0]         = TRUE;//rendering
	m_flags[1]         = FALSE;//selected
	m_flags[2]         = TRUE;//pushable
	m_flags[3]         = FALSE;//blocked
	m_flags[4]         = FALSE;//collision with tilemap
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
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



void Model::InitializeSpriteModel(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader,ModelPaths* paths, float spriteSize)
{
	m_spriteModel = new SpriteModel(spriteSize);
	dynamic_cast<SpriteModel*>(m_spriteModel)->Initialize(device, deviceContext, shader,paths);
	m_size = spriteSize;
	m_lastsize = spriteSize;
}





void Model::Update(float dt)
{
	if (!m_flags[3])
	{
		if (!m_spriteModel->IsLocked())
		{
			m_floats[1] = Center;
			if (XMVectorGetIntX < 0)
			{
				Center.x -= m_floats[0].x * dt;
				Center.y -= m_floats[0].y * dt;
				//	Center.z -= m_velocity.z * dt;

			}
			else
			{
				Center.x += m_floats[0].x * dt;
				Center.y += m_floats[0].y * dt;
				//Center.z += m_velocity.z * dt;
			}
		}

		if (m_spriteModel&&m_flags[0])
		{
			XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y + (m_size / 1.5f), Center.z - (m_size / 1.5f)));
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

void Model::__Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,ShaderPackage &shader)
{
	if (m_spriteModel&&m_flags[0])
	{

		//shader.standard->End(deviceContext);
		//shader.shadow->Begin(deviceContext);
		//
		//auto cmm = Camera::GetCurrentCamera();
		//auto cpp = cmm->GetPosition();
		//
		////auto cxvm = XMLoadFloat3(&Center);
		//
		////auto cxm = XMVector2AngleBetweenVectors(cpp, cxvm);
		//
		//__m128 dist{};
		//dist.m128_f32[0] = cpp.m128_f32[1] - Center.y;
		//dist.m128_f32[1] = cpp.m128_f32[0] - Center.x;
		//
		//auto rot = atan2(dist.m128_f32[0], dist.m128_f32[1]);
		//
		//auto wms = XMMatrixRotationZ(rot + XM_PIDIV2);
		//
		////	auto distL = XMVector2Length(dist).m128_f32[0];
		//
		//	//auto txscl = distL / 1000.0f;
		//
		//	//ipp::math::clamp(txscl, 0.0f, 3.0f);
		//
		////	auto scl = XMMatrixScaling(distL / 1000.0f, distL / 1000.0f, distL / 1000.0f);
		//
		//
		//
		//wms = wms * XMLoadFloat4x4(&m_worldMatrix);// * scl;
		//XMFLOAT4X4 shadowMatrix;
		//XMStoreFloat4x4(&shadowMatrix, wms);
		//m_spriteModel->Render(deviceContext, shadowMatrix, viewMatrix, projectionMatrix, shader.shadow);
		//
		//shader.shadow->End(deviceContext);
		//shader.standard->Begin(deviceContext);


		m_spriteModel->Render(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix,shader.standard);
		//if (m_flags[1])
		//{
		//	m_spriteModel->DrawRectangle(deviceContext, shader,1);
		//}
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
	return m_floats[0];
}

float Model::GetRotation()
{
	return m_spriteModel->m_rotation / 16.0f;
}

void Model::GoBack()
{
	Center = m_floats[1];
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
	Center.y -= (m_lastsize/2.0f);
	Center.z = z;
}

void Model::SetPosition(XMFLOAT3 position)
{
	Center = position;
}

void Model::SetVelocity(float x, float y,float z)
{
	m_floats[0].x = x;
	m_floats[0].y = y;
	m_floats[0].z = z;
}

void Model::SetVelocity(float velocity[3])
{
	m_floats[0].x = velocity[0];
	m_floats[0].y = velocity[1];
	m_floats[0].z = velocity[2];
}

void Model::SetVelocity(XMFLOAT3 velocity)
{
	m_floats[0] = velocity;
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

void Model::SetRotations(float rotations)
{
	m_spriteModel->SetRotations(rotations);
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



