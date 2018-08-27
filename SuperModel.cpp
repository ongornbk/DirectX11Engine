#include "SuperModel.h"
#include "ResourceManager.h"

namespace
{
#define FRAMES_SUM 32

	static ID3D11ShaderResourceView* m_textures[20];
	static int                       m_framesBegin[7] = { 0,4,12,16,18,24,28 };
	static int                       m_frames[7]      = { 4,8,4, 2, 6, 4, 4  };
}

SuperModel::SuperModel(ModelEquipmentAndGender model, float size) : RenderModel()
{
	m_vertexBuffer = nullptr;
	m_size = size;
	m_rotation = 0.0f;
	m_isLooping = true;
	m_animationSpeed = 0.25f;
	m_framesPerSecond = 1.0f;
	m_currentSpeed = 0.0f;
	m_stop = false;
	m_rotations = 16.0f;
	m_equipmentAndGender = model;
}


SuperModel::~SuperModel()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void SuperModel::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR * filename)
{
	RenderModel::Initialize(device,deviceContext,shader,filename);
	float sizexy[2] = { m_size,m_size };
	m_vertexBuffer = new VertexBuffer();
	m_vertexBuffer->Initialize(device, shader, sizexy, true);
	m_currentFrame = 0.0f;
	m_previousFrame = -1.0f;
}

void SuperModel::Update(float dt)
{
}

void SuperModel::Render(XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
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
	m_shader->SetShaderParameters(m_deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	RenderModel::Render(worldMatrix, viewMatrix, projectionMatrix);
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
	m_shader->SetShaderParameters(m_deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	RenderModel::Render(worldMatrix, viewMatrix, projectionMatrix);
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
