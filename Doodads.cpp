#include "Doodads.h"
#include "RendererManager.h"
#include "IPP.h"

using ipp::memory_cast;

Doodads::Doodads()
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	Radius = 0.0f;

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
}

Doodads::~Doodads()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void Doodads::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR * paths, float size, float collision, XMFLOAT3 position,RenderContainerFlags flags)
{

	m_size = size;

	m_vertexBuffer = new VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);

	if (paths != NULL)
	{
		wstring tmp0 = wstring(paths);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	
	m_deviceContext = deviceContext;

	
	m_flags = flags.m_flags;

	Radius = collision;
	Center = position;
	Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;


	m_type = RenderContainer::RenderContainerType::DOODADS;

	

}

void Doodads::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader)
{
	if (m_rendering)
	{
		if (m_cast_shadow)
		{
			shader.standard->End(deviceContext);

			shader.shadow->Begin(deviceContext);
			shader.shadow->SetShaderParameters(deviceContext, m_texture->GetTexture());
			shader.shadow->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
			m_vertexBuffer->Render(deviceContext);
			shader.shadow->End(deviceContext);

			shader.standard->Begin(deviceContext);
		}

		shader.standard->SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.standard->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);
	}
}

void Doodads::Update(float dt)
{

	m_rendering = validateRendering(Center);
	if (m_rendering)
	{
		XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y + (m_size / 1.5f), Center.z - (m_size / 1.5f)));
	}

}

void Doodads::SetZ(float z)
{
	Center.z = z;
}

BoundingSphere * Doodads::GetBoundingSphere()
{
	return (BoundingSphere*)(this);
}

void Doodads::Release()
{
	delete this;
}

