#include "Tree.h"
#include "ResourceManager.h"
#include "RendererManager.h"
#include "IPP.h"

namespace
{
	static Global* m_global = nullptr;
}

Tree::Tree()
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	Radius = 0.0f;

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
}


Tree::~Tree()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void Tree::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR * paths, float size, float collision, XMFLOAT3 position, RenderContainerFlags flags)
{
	m_size = size;


	m_vertexBuffer = new VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->InitializeAnchorBottom(device, shader, sizexy, true);

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

	m_type = RenderContainer::RenderContainerType::TREE;
}

void Tree::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader)
{
	if (m_rendering)
	{

		if (m_cast_shadow)
		{
			shader.standard->End(deviceContext);
			shader.shadow->Begin(deviceContext);

			__m128 cameraPosition = Camera::GetCurrentCamera()->GetPosition();

			__m128 distance{};
			distance.m128_f32[0] = cameraPosition.m128_f32[1] - Center.y;
			distance.m128_f32[1] = cameraPosition.m128_f32[0] - Center.x;

			float rotation = atan2(distance.m128_f32[0], distance.m128_f32[1]);

			DirectX::XMMATRIX rotationMatrix = XMMatrixRotationZ(rotation + XM_PIDIV2);

			float length = XMVector2Length(distance).m128_f32[0];

			rotationMatrix = rotationMatrix * XMLoadFloat4x4(&m_worldMatrix);
			XMFLOAT4X4 shadowMatrix;
			XMStoreFloat4x4(&shadowMatrix, rotationMatrix);
			shader.shadow->SetShaderParameters(deviceContext, m_texture->GetTexture());
			shader.shadow->SetShaderParameters(deviceContext, shadowMatrix, viewMatrix, projectionMatrix);
			m_vertexBuffer->Render(deviceContext);

			shader.shadow->End(deviceContext);
			shader.standard->Begin(deviceContext);
		}

		shader.standard->SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.standard->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);

	}
}

void Tree::Update(float dt)
{
	m_rendering = validateRendering(Center);
	if (m_rendering)
	{
		XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y, Center.z));
	}
}

void Tree::SetZ(float z)
{
	Center.z = z;
}

BoundingSphere * Tree::GetBoundingSphere()
{
	return (BoundingSphere*)(this);
}

void Tree::Release()
{
	delete this;
}

void Tree::SetGlobal(Global * global) noexcept
{
	m_global = global;
}
