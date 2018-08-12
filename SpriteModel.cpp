#include "SpriteModel.h"
#include "Onion.h"
#include "Engine.h"

using Onion::Timer;

#define SPRITEMODEL_DEFAULT_ROTATION       0.0f
#define SPRITEMODEL_DEFAULT_ROTATION_SPEED 0.01f

SpriteModel::SpriteModel(float size)
{
	m_modelVariant.SetVariant(TOWNNEUTRAL);
	m_vertexBuffer = NULL;
	m_size = size;
	m_rotation = SPRITEMODEL_DEFAULT_ROTATION;
	m_isLooping = true;
	m_animationSpeed = 0.25f;
	m_framesPerSecond = 1.0f;
	m_currentSpeed = 0.0f;
	m_stop = false;
	m_rotations = 16.0f;
}


SpriteModel::~SpriteModel(void)
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = NULL;
	}

}


void SpriteModel::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader,ModelPaths* paths)
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

void SpriteModel::Update(float dt)
{
	if (m_modelVariant.GetMaxFrames() == 1.0f) return;
	if (m_currentFrame < m_modelVariant.GetMaxFrames())
	{
		m_currentSpeed += m_animationSpeed + dt;

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
	VertexBuffer::VertexType* vertices = m_vertexBuffer->GetVertices();

	vertices[0].uv.x = m_currentFrame / m_modelVariant.GetMaxFrames();
	vertices[0].uv.y = (m_rotation + 1.0f) / m_rotations;

	vertices[1].uv.x = m_currentFrame / m_modelVariant.GetMaxFrames();
	vertices[1].uv.y = m_rotation / m_rotations;

	vertices[2].uv.x =( m_currentFrame+1.0f) / m_modelVariant.GetMaxFrames();
	vertices[2].uv.y = m_rotation / m_rotations;

	vertices[3].uv.x = (m_currentFrame + 1.0f) / m_modelVariant.GetMaxFrames();
	vertices[3].uv.y = (m_rotation + 1.0f) / m_rotations;



	HRESULT result = m_deviceContext->Map(m_vertexBuffer->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return;
	}

	VertexBuffer::VertexType* verticesPtr = (VertexBuffer::VertexType*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, sizeof(VertexBuffer::VertexType) * m_vertexBuffer->GetVertexCount());
	m_deviceContext->Unmap(m_vertexBuffer->GetVertexBuffer(), 0);

	m_previousFrame = m_currentFrame;


}

void SpriteModel::Resize(ID3D11Device * device, Shader * shader, float resize)
{
	m_size *= resize;
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);
}

void SpriteModel::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,Shader* shader)
{

		shader->SetShaderParameters(deviceContext, m_modelVariant.GetTexture(),m_modelVariant.GetVariant());
		shader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, m_modelVariant.GetVariant());
		m_vertexBuffer->Render(deviceContext);

}

void SpriteModel::SetRotation(int rotation)
{
	(this->m_rotation) = (float)(rotation % (int)m_rotations);
	//float rotation0 = (float)(rotation % (int)ROTATIONS);
	//switch (rotation0 > (this->m_rotation))
	//{
	//case true:
	//{
	//	switch ((this->m_rotation) >= (ROTATIONS - 1.0f))
	//	{
	//	case true:
	//	{
	//		(this->m_rotation) = 0.0f;
	//		break;
	//	}
	//	case false:
	//	{
	//		(this->m_rotation) += SPRITEMODEL_DEFAULT_ROTATION_SPEED;
	//		break;
	//	}
	//	}
	//	break;
	//}
	//case false:
	//{
	//	switch ((this->m_rotation) <= 0.0f)
	//	{
	//	case true:
	//	{
	//		(this->m_rotation) = (ROTATIONS - 1.0f);
	//		break;
	//	}
	//	case false:
	//	{
	//		(this->m_rotation) -= SPRITEMODEL_DEFAULT_ROTATION_SPEED;
	//		break;
	//	}
	//	}
	//	break;
	//}
	//}
}

void SpriteModel::PlayAnimation(ModelStance animation)
{
	if (!m_stop)
	{
		m_currentFrame = 0.0f;
		m_previousFrame = -1.0f;
		m_stopped = m_modelVariant.GetVariant();
		m_modelVariant.SetVariant(animation);
		m_isLooping = false;
		m_stop = true;
	}
		
}

bool SpriteModel::IsLocked()
{
	return m_stop;
}

void SpriteModel::DrawRectangle(ID3D11DeviceContext * deviceContext, Shader* shader, int borderWidth)
{
	//deviceContext->
}

void SpriteModel::SetRotations(float rotations)
{
	this->m_rotations = rotations;
	//m_modelVariant.m_maxFrames[10] = 22;
}

void SpriteModel::SetAnimation(ModelStance animation, bool lock, bool force)
{

	if (m_modelVariant.GetVariant() != animation&&!m_stop)
	{
		m_currentFrame = 0.0f;
		m_previousFrame = -1.0f;
		m_modelVariant.SetVariant(animation);
	}

}

void SpriteModel::SetAnimationSpeed(float speed)
{
	this->m_previousSpeed = m_animationSpeed;
	this->m_animationSpeed = speed;
}

