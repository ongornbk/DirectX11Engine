#include "SuperModel.h"
#include "ResourceManager.h"

namespace
{
#define FRAMES_SUM 32

	static ID3D11ShaderResourceView* m_textures[20];
	static int                       m_framesBegin[7] = { 0,4,12,16,18,24,28 };
	static int                       m_framesEnd[7] = { 4,12,16,18,24,28,32 };
	static int                       m_frames[7]      = { 4,8,4, 2, 6, 4, 4  };
	static Shader*                   m_shader = nullptr;
	static ID3D11Device*             m_device = nullptr;
	static ID3D11DeviceContext*      m_deviceContext = nullptr;
	static SuperModel::ModelStance   m_stopped = SuperModel::ModelStance::STANCE;
}

SuperModel::SuperModel(ModelEquipmentAndGender model, float size) : CollisionCircle()
{
	m_vertexBuffer = nullptr;
	m_size = size;
	m_rotation = 0.0f;
	m_isLooping = true;
	m_animationSpeed = 0.25f;
	m_framesPerSecond = 1.0f;
	m_currentSpeed = 0.0f;
	m_stop = false;
	m_rotations = 16u;
	m_equipmentAndGender = model;
	m_velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_lastPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
}


SuperModel::~SuperModel()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void SuperModel::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader)
{
	m_shader = shader;
	m_device = device;
	m_deviceContext = deviceContext;
	float sizexy[2] = { m_size,m_size };
	m_vertexBuffer = new VertexBuffer();
	m_vertexBuffer->Initialize(device, shader, sizexy, true);
	m_currentFrame = 0.0f;
	m_previousFrame = -1.0f;
}

void SuperModel::Update(float dt)
{
	if (!f_blocked)
	{
		if (!f_locked)
		{
			m_lastPosition = Center;
			if (XMVectorGetIntX < 0)
			{
				Center.x -= m_velocity.x * dt;
				Center.y -= m_velocity.y * dt;
			}
			else
			{
				Center.x += m_velocity.x * dt;
				Center.y += m_velocity.y * dt;
			}
		}

		if (f_rendering)
		{
			XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y + (m_size / 1.5f), Center.z - (m_size / 1.5f)));

			int endframe = m_framesEnd[m_stance];
			int beginframe = m_framesBegin[m_stance];
			int framesCount = m_frames[m_stance];
			

			if (m_currentFrame < endframe)
			{
				m_currentSpeed += m_animationSpeed + dt;

				if (m_currentSpeed > m_framesPerSecond)
				{
					m_currentFrame++;
					m_currentSpeed = 0.0f;
					if (m_currentFrame >= endframe)
					{
						if (m_isLooping)
						{
							m_currentFrame = (float)beginframe;
						}
						else
						{
							m_stop = false;
							m_isLooping = true;
							m_currentFrame = (float)beginframe;
							m_previousFrame = -1.0f;
							m_stance = m_stopped;
						}
					}

				}
			}
			if (m_currentFrame == m_previousFrame) return;





			D3D11_MAPPED_SUBRESOURCE mappedResource;
			SpriteVertexType* vertices = m_vertexBuffer->GetVertices();

			vertices[0].uv.x = m_currentFrame / framesCount;
			vertices[0].uv.y = (m_rotation + 1.0f) / m_rotations;

			vertices[1].uv.x = m_currentFrame / framesCount;
			vertices[1].uv.y = m_rotation / m_rotations;

			vertices[2].uv.x = (m_currentFrame + 1.0f) / framesCount;
			vertices[2].uv.y = m_rotation / m_rotations;

			vertices[3].uv.x = (m_currentFrame + 1.0f) / framesCount;
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
	}
}

void SuperModel::Render(XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	switch (m_equipmentAndGender.m_head)
	{
	case HEAD1:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[0]);
		break;
	case HEAD2:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[1]);
		break;
	case HEAD3:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[2]);
		break;
}
	m_shader->SetShaderParameters(m_deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(m_deviceContext);
	switch (m_equipmentAndGender.m_armor)
	{
	case CLOTH:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[3]);
		break;
	case LEATHER:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[4]);
		break;
	case STEEL:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[5]);
		break;
	}
	m_shader->SetShaderParameters(m_deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(m_deviceContext);
	switch (m_equipmentAndGender.m_weapon.m_weaponType)
	{
	case Weapon::MELEE:
		switch (m_equipmentAndGender.m_weapon.m_melee)
		{
		case DAGGER:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[6]);
			break;
		case SHORTSWORD:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[7]);
			break;
		case LONGSWORD:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[8]);
			break;
		case GREATSWORD:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[9]);
			break;
		}
		break;
	case Weapon::RANGED:
		switch (m_equipmentAndGender.m_weapon.m_ranged)
		{
		case SLINGSHOT:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[10]);
			break;
		case SHORTBOW:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[11]);
			break;
		case LONGBOW:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[12]);
			break;
		case GREATBOW:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[13]);
			break;
		}
		break;
	case Weapon::MAGIC:
		switch (m_equipmentAndGender.m_weapon.m_ranged)
		{
		case WAND:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[14]);
			break;
		case ROD:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[15]);
			break;
		case STAFF:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[16]);
			break;
		case GREATSTAFF:
			m_shader->SetShaderParameters(m_deviceContext, m_textures[17]);
			break;
		}
		break;
	}
	m_shader->SetShaderParameters(m_deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(m_deviceContext);
	switch (m_equipmentAndGender.m_shield)
	{
	case BUCKLER:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[18]);
		break;
	case SHIELD:
		m_shader->SetShaderParameters(m_deviceContext, m_textures[19]);
		break;
	}
	m_shader->SetShaderParameters(m_deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(m_deviceContext);
}

void SuperModel::SetRotation(uint16_t rotation)
{
	this->m_rotation = (float)(rotation % (this->m_rotations));
}

void SuperModel::InitializeTextures()
{
	m_textures[0] = ResourceManager::GetInstance()->GetTextureByName("male_head1")->GetTexture();
	m_textures[1] = ResourceManager::GetInstance()->GetTextureByName("male_head2")->GetTexture();
	m_textures[2] = ResourceManager::GetInstance()->GetTextureByName("male_head3")->GetTexture();
	m_textures[3] = ResourceManager::GetInstance()->GetTextureByName("clothes")->GetTexture();
	m_textures[4] = ResourceManager::GetInstance()->GetTextureByName("leather_armor")->GetTexture();
	m_textures[5] = ResourceManager::GetInstance()->GetTextureByName("steel_armor")->GetTexture();
	m_textures[6] = ResourceManager::GetInstance()->GetTextureByName("dagger")->GetTexture();
	m_textures[7] = ResourceManager::GetInstance()->GetTextureByName("shortsword")->GetTexture();
	m_textures[8] = ResourceManager::GetInstance()->GetTextureByName("longsword")->GetTexture();
	m_textures[9] = ResourceManager::GetInstance()->GetTextureByName("greatsword")->GetTexture();
	m_textures[10] = ResourceManager::GetInstance()->GetTextureByName("slingshot")->GetTexture();
	m_textures[11] = ResourceManager::GetInstance()->GetTextureByName("shortbow")->GetTexture();
	m_textures[12] = ResourceManager::GetInstance()->GetTextureByName("longbow")->GetTexture();
	m_textures[13] = ResourceManager::GetInstance()->GetTextureByName("greatbow")->GetTexture();
	m_textures[14] = ResourceManager::GetInstance()->GetTextureByName("wand")->GetTexture();
	m_textures[15] = ResourceManager::GetInstance()->GetTextureByName("rod")->GetTexture();
	m_textures[16] = ResourceManager::GetInstance()->GetTextureByName("staff")->GetTexture();
	m_textures[17] = ResourceManager::GetInstance()->GetTextureByName("greatstaff")->GetTexture();
	m_textures[18] = ResourceManager::GetInstance()->GetTextureByName("buckler")->GetTexture();
	m_textures[19] = ResourceManager::GetInstance()->GetTextureByName("shield")->GetTexture();
}
