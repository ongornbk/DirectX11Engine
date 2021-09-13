#include "Sprite.h"
#include "ResourceManager.h"
#include "GlobalUtilities.h"

Sprite::Sprite(float size) : ColorFilter(1.f,1.f,1.f,1.f)
{
	m_vertexBuffer = NULL;
	m_texture = NULL;
	m_size.x = size;
	m_size.y = size;
}

Sprite::Sprite(float sizex, float sizey) : ColorFilter(1.f, 1.f, 1.f, 1.f)
{
	m_vertexBuffer = NULL;
	m_texture = NULL;
	m_size.x = sizex;
	m_size.y = sizey;
}


Sprite::~Sprite(void)
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = NULL;
	}

}

void Sprite::Initialize(ID3D11Device * device, Shader * shader, WCHAR* textureFileName,bool isWriteable)
{
	m_shader = shader;
	m_vertexBuffer = new VertexBuffer();
	(void)m_vertexBuffer->InitializeAnchorTopLeft(device,shader,m_size,isWriteable);

	if (textureFileName != NULL)
	{
		wstring tmp0 = wstring(textureFileName);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	
}

void Sprite::InitializeRotated(ID3D11Device * device, Shader * shader, WCHAR * textureFileName, bool isWriteable)
{

}

void Sprite::Update()
{
}

void Sprite::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	if (m_texture)
	{
		m_shader->SetShaderParameters(deviceContext, m_texture->GetTexture());
		m_shader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
		m_shader->SetShaderColorParameters(deviceContext, m_colorFilter);
		m_vertexBuffer->Render(deviceContext);
	}
}

void Sprite::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader* shader)
{

	shader->SetShaderParameters(deviceContext,m_texture->GetTexture());
	shader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(deviceContext);

}



bool Sprite::ResizeTexture(ID3D11Device * device, float size, bool writeable)
{
	if (m_size.x != size)
	{
		m_size.x = size;
		return m_vertexBuffer->ResizeTexture(device, size, writeable);
	}
	return true;
}

void Sprite::SetAnimationSpeed(float speed)
{
}

const DirectX::XMFLOAT2 Sprite::GetSize() const noexcept
{
	return m_size;
}
