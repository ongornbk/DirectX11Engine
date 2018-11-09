#include "Unit.h"
#include "Engine.h"
#include "S_ModelPaths.h"
#include "RendererManager.h"
#include "IPP.h"

Unit::Unit() : Model()
{
	//m_yOffset = 0.0f;
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
	Model::Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix
	Model::Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix
	m_wanderingFlag = wander;
	m_type = RenderContainer::RenderContainerType::UNIT;
}

void Unit::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader)
{
	if (m_flags[0])
	{
		//Model::__Render(deviceContext, viewMatrix, projectionMatrix, shader.shadow);

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
		//shader.shadow->SetShaderParameters(deviceContext, m_texture->GetTexture());
		//shader.shadow->SetShaderParameters(deviceContext, shadowMatrix, viewMatrix, projectionMatrix);
		////m_vertexBuffer->Render(deviceContext);
		//
		//shader.shadow->End(deviceContext);
		//shader.standard->Begin(deviceContext);

		//if (this==Global::GetInstance()->m_lastSelectedUnit)
		//{
		//	shader.standard->End(deviceContext);
		//	shader.select->Begin(deviceContext);
		//	Model::__Render(deviceContext, viewMatrix, projectionMatrix, shader.select);
		//	shader.select->End(deviceContext);
		//	shader.standard->Begin(deviceContext);
		//}
		Model::__Render(deviceContext, viewMatrix, projectionMatrix, shader);
	}

}



void Unit::Update(float dt)
{
	//if (m_yOffset > 0.0f)
	//	Center.y += m_yOffset;
	//else
	//	Center.y -= m_yOffset;
	//m_yOffset = 0.0f;

	if (!m_tasks.Update())if(m_wanderingFlag)m_tasks.Wander(this);

	Model::SetRenderingStance(validateRendering(Model::Center));

	Model::Update(dt);

	

	int16_t mousePosition[2];
	UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
	FXMVECTOR point = XMVectorSet((float)mousePosition[0], (float)mousePosition[1], 0.0f, 0.0f);
	if (Model::BoundingSphere::Contains(point))
	{
		//Model::GoBack();
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

void Unit::SetZ(float z)
{
	Center.z = z;
}

void Unit::SetTask(Task* task)
{
	m_tasks.SetTask(task);
}

void Unit::GiveTask(Task * task)
{
	m_tasks.QueueTask(task);
}

void Unit::Release()
{
	delete this;
}

bool Unit::Flag(uint8_t index)
{
	return m_flags[index];
}

void Unit::Flag(uint8_t index, bool boolean)
{
	m_flags[index] = boolean;
}





float Unit::GetCollisionRadius()
{
	return Model::Radius;
}

BoundingSphere* Unit::GetBoundingSphere()
{
	return (BoundingSphere*)(this);
}

XMFLOAT3 Unit::GetPosition()
{
	return Model::Center;
}

float Unit::GetSpeed()
{
	return m_speed[0];
}

float Unit::GetZ()
{
	return Center.z;
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



