#include "Unit.h"
#include "Engine.h"
#include "S_ModelPaths.h"
#include "RendererManager.h"
#include "IPP.h"

Unit::Unit()
{
	m_floats[0] = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_floats[1] = XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
	m_modelVariant.SetVariant(MS_TOWNNEUTRAL);
	m_vertexBuffer = nullptr;
	m_rotation = DEFAULT_ROTATION;
	m_isLooping = true;
	m_animationSpeed = 0.20f;
	m_framesPerSecond = 1.0f;
	m_currentSpeed = 0.0f;
	m_stop = false;
	m_rotations = 16.0f;
}


Unit::~Unit()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = NULL;
	}
}

void Unit::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR* paths, float modelsize, float collision, XMFLOAT3 position,RenderContainerFlags flags, bool wander)
{
	wstring tmp0 = wstring(paths);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	ModelPaths* ptr = S_ModelPaths::GetModelPaths(tmp1);



	m_size = modelsize;
	m_lastSize = modelsize;
	Radius = collision;
	Center = position;
	Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;

	InitializeModel(device, deviceContext, shader, ptr);
	m_wanderingFlag = wander;
	m_type = RenderContainer::RenderContainerType::UNIT;

	m_flags = flags.m_flags;
}

void Unit::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader)
{
	if (m_rendering)
	{
		Shader* csh = shader.standard;
		
		csh->SetShaderParameters(deviceContext, m_modelVariant.GetTexture());
		csh->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);
	}

}



void Unit::Update(float dt)
{

	
	m_rendering = validateRendering(Center);

	if (!m_blocked)
	{

		if (m_tasks.Update())
		{

		}
		else
		{
			if (m_wanderingFlag)
			{
				m_tasks.Wander(this);
			}
			else
			{
				SetAnimation(ModelStance::MS_TOWNNEUTRAL);
				SetVelocity(0.0f, 0.0f, 0.0f);
			}
		}
		
			

		if (!m_stop)
		{
			m_floats[1] = Center;
			if (XMVectorGetIntX < 0)
			{
				Center.x -= m_floats[0].x * dt;
				Center.y -= m_floats[0].y * dt;
			}
			else
			{
				Center.x += m_floats[0].x * dt;
				Center.y += m_floats[0].y * dt;
			}
		}

		if (m_rendering)
		{

			XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y + (m_size / 1.5f), Center.z - (m_size / 1.5f)));


			if (m_modelVariant.GetMaxFrames() == 1.0f) return;
			if (m_currentFrame < m_modelVariant.GetMaxFrames())
			{
				m_currentSpeed += m_animationSpeed - dt;

				if (m_currentSpeed > m_framesPerSecond)
				{
					m_currentFrame++;
					m_currentSpeed = 0.0f;
					if (m_currentFrame >= m_modelVariant.GetMaxFrames())
					{
						if (m_isLooping)
						{
							m_currentFrame = 0.0f;
						}
						else
						{
							m_stop = false;
							m_isLooping = true;
							m_currentFrame = 0.0f;
							m_previousFrame = -1.0f;
							m_modelVariant.SetVariant(m_stopped);
						}
					}

				}
			}
			if (m_currentFrame == m_previousFrame) return;





			D3D11_MAPPED_SUBRESOURCE mappedResource;
			SpriteVertexType* vertices = m_vertexBuffer->GetVertices();

			vertices[0].uv.x = m_currentFrame / m_modelVariant.GetMaxFrames();
			vertices[0].uv.y = (m_rotation + 1.0f) / m_rotations;

			vertices[1].uv.x = m_currentFrame / m_modelVariant.GetMaxFrames();
			vertices[1].uv.y = m_rotation / m_rotations;

			vertices[2].uv.x = (m_currentFrame + 1.0f) / m_modelVariant.GetMaxFrames();
			vertices[2].uv.y = m_rotation / m_rotations;

			vertices[3].uv.x = (m_currentFrame + 1.0f) / m_modelVariant.GetMaxFrames();
			vertices[3].uv.y = (m_rotation + 1.0f) / m_rotations;



			HRESULT result = m_deviceContext->Map(m_vertexBuffer->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			if (FAILED(result))
			{
				return;
			}

			SpriteVertexType* verticesPtr = (SpriteVertexType*)mappedResource.pData;
			memcpy(verticesPtr, (void*)vertices, sizeof(SpriteVertexType) * m_vertexBuffer->GetVertexCount());
			m_deviceContext->Unmap(m_vertexBuffer->GetVertexBuffer(), 0);

			m_previousFrame = m_currentFrame;

		}




		int16_t mousePosition[2];
		UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
		FXMVECTOR point = XMVectorSet((float)mousePosition[0], (float)mousePosition[1], 0.0f, 0.0f);
		if (BoundingSphere::Contains(point))
		{
			m_selected = true;
			GLOBAL m_lastSelectedUnit = this;
		}
		else
		{
			m_selected = false;
		}
		if (TileMap::CollisionAt(Center))
		{
			Center = m_floats[1];
			m_collided = true;
		}
		else
		{
			m_collided = false;
		}
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

float Unit::GetCollisionRadius()
{
	return Radius;
}


XMFLOAT3 Unit::GetPosition()
{
	return Center;
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
	case WS_WALK:
		m_speed[0] = m_speed[1] / 2.0f;
		break;
	case WS_RUN: 
		m_speed[0] = m_speed[1];
		break;
	}
}

void Unit::ChangeWalkingStance()
{
	switch (m_walkingStance)
	{
	case Unit::WalkingStance::WS_RUN:
			m_walkingStance = Unit::WalkingStance::WS_WALK;
			m_speed[0] = m_speed[1] / 2.0f;
			break;
	case Unit::WalkingStance::WS_WALK:
		m_walkingStance = Unit::WalkingStance::WS_RUN;
		m_speed[0] = m_speed[1];
		break;
	}
}

void Unit::SetRotations(int32_t rotations)
{
	(this->m_rotation) = (float)(rotations % (int32_t)m_rotations);
}

void Unit::SetRotation(float rotation)
{
	m_rotation = (int32_t)rotation % (int32_t)m_rotations;
}

void Unit::SetVelocity(float x, float y, float z)
{
	m_floats[0] = { x,y,z };
}

void Unit::DiscardTasks()
{
	m_tasks.Discard();
}

void Unit::SetPosition(XMFLOAT3 position)
{
	Center = position;
}

void Unit::GoBack()
{
	Center = m_floats[1];
}

void Unit::Resize(ID3D11Device * device, Shader * shader, float resize)
{
	m_size *= resize;
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);
}

void Unit::PlayAnimation(ModelStance animation)
{
	if (m_rendering&&!m_stop)
	{
		m_currentFrame = 0.0f;
		m_previousFrame = -1.0f;
		m_stopped = m_modelVariant.GetVariant();
		m_modelVariant.SetVariant(animation);
		m_isLooping = false;
		m_stop = true;
	}
}

void Unit::SetAnimation(ModelStance animation)
{
	if (m_rendering && !m_stop&&(animation!=m_modelVariant.GetVariant()))
	{
		m_currentFrame = 0.0f;
		m_previousFrame = -1.0f;
		m_modelVariant.SetVariant(animation);
	}
}

void Unit::SetAnimationSpeed(float speed)
{
	m_previousSpeed = m_animationSpeed;
	m_animationSpeed = speed;
}

void Unit::InitializeModel(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, ModelPaths * paths)
{
	m_vertexBuffer = new VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);


	if (paths->TOWNWALK != NULL)
	{
		wstring tmp0 = wstring(paths->TOWNWALK);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[0] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	if (paths->TOWNNEUTRAL != NULL)
	{
		wstring tmp0 = wstring(paths->TOWNNEUTRAL);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[1] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	if (paths->SPECIALCAST != NULL)
	{
		wstring tmp0 = wstring(paths->SPECIALCAST);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[2] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	if (paths->GETHIT != NULL)
	{
		wstring tmp0 = wstring(paths->GETHIT);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[3] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->KICK != NULL)
	{
		wstring tmp0 = wstring(paths->KICK);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[4] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->SPECIAL_1 != NULL)
	{
		wstring tmp0 = wstring(paths->SPECIAL_1);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[5] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->WALK != NULL)
	{
		wstring tmp0 = wstring(paths->WALK);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[6] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->ATTACK_1 != NULL)
	{
		wstring tmp0 = wstring(paths->ATTACK_1);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[7] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->NEUTRAL != NULL)
	{
		wstring tmp0 = wstring(paths->NEUTRAL);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[8] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->ATTACK_2 != NULL)
	{
		wstring tmp0 = wstring(paths->ATTACK_2);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[9] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->RUN != NULL)
	{
		wstring tmp0 = wstring(paths->RUN);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[10] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->SPECIAL_3 != NULL)
	{
		wstring tmp0 = wstring(paths->SPECIAL_3);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[11] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->SPECIAL_4 != NULL)
	{
		wstring tmp0 = wstring(paths->SPECIAL_4);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[12] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}



	m_deviceContext = deviceContext;
	m_currentFrame = 0.0f;
	m_previousFrame = -1.0f;
}



