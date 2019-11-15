#include "Doodads.h"
#include "RendererManager.h"
#include "IPP.h"

using ipp::memory_cast;

Doodads::Doodads()
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	m_boundingSphere.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_boundingSphere.Radius = 0.0f;

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

void Doodads::Initialize(
	ID3D11Device * device,
	ID3D11DeviceContext * deviceContext,
	class Shader * shader,
	WCHAR * paths,
	const float size,
	const float collision,
	const XMFLOAT3 position
	)
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

	m_boundingSphere.Radius = collision;
	m_boundingSphere.Center = position;
	m_boundingSphere.Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	m_boundingSphere.Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;


	m_type = EObject::EObjectType::DOODADS;

	

}

void Doodads::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct XMFLOAT4X4& viewMatrix,
	const struct XMFLOAT4X4& projectionMatrix,
	const struct ShaderPackage &shader
)
{
	if (m_flags.m_rendering)
	{
		shader.standard->SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.standard->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);
	}
}

void Doodads::PreRender(ID3D11DeviceContext * const deviceContext, const DirectX::XMFLOAT4X4 & viewMatrix, const DirectX::XMFLOAT4X4 & projectionMatrix, const ShaderPackage & shader)
{
	if (m_flags.m_rendering)
	{
		if (m_flags.m_cast_shadow)
		{
			//shader.standard->End(deviceContext);

			//shader.shadow->Begin(deviceContext);
			shader.shadow->SetShaderParameters(deviceContext, m_texture->GetTexture());
			shader.shadow->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
			m_vertexBuffer->Render(deviceContext);
			//shader.shadow->End(deviceContext);

			//shader.standard->Begin(deviceContext);
		}
	}
}

void Doodads::Update(float dt)
{

	m_flags.m_rendering = validateRendering(m_boundingSphere.Center);
	if (m_flags.m_rendering)
	{
		XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(m_boundingSphere.Center.x, m_boundingSphere.Center.y + (m_size / 1.5f), m_boundingSphere.Center.z - (m_size / 1.5f)));
	}

}

void Doodads::SetZ(float z)
{
	m_boundingSphere.Center.z = z;
}

void Doodads::Release()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

int32 Doodads::isReleased() const noexcept
{
	if (m_vertexBuffer)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
