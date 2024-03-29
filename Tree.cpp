#include "Tree.h"
#include "ResourceManager.h"
#include "RendererManager.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"
#include "IPP.h"

namespace
{
	static Global* m_global = nullptr;
}

Tree::Tree() :
	ColorFilter(1.f,1.f,1.f,1.f)
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_boundingSphere.Radius = 0.0f;

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

	m_stance = 0;
}


Tree::~Tree()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void Tree::Initialize(
	ID3D11Device * device,
	ID3D11DeviceContext * deviceContext,
	Shader * shader,
	WCHAR * paths,
	const float size,
	const float collision,
	const XMFLOAT3 position
)
{
	m_size = size;

	m_vertexBuffer = new class VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->InitializeAnchorBottom(device, shader, sizexy, true);

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

	m_type = EObject::EObjectType::OBJECT_TYPE_TREE;
}

void Tree::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct XMFLOAT4X4& viewMatrix,
	const struct XMFLOAT4X4& projectionMatrix,
	const struct ShaderPackage &shader)
{
	if (m_flags.m_rendering)
	{
		shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		shader.SetShaderColorParameters(deviceContext, m_colorFilter);
		m_vertexBuffer->Render(deviceContext);
	}
}

void Tree::PreRender(
	struct ID3D11DeviceContext * const deviceContext,
	const struct DirectX::XMFLOAT4X4 & viewMatrix,
	const struct DirectX::XMFLOAT4X4 & projectionMatrix,
	const struct ShaderPackage & shader
)
{
	if (m_flags.m_rendering && m_flags.m_cast_shadow)
	{
		//shader.standard->End(deviceContext);
		//shader.shadow->Begin(deviceContext);

		const __m128 cameraPosition = Camera::GetCurrentCamera()->GetPosition();

		__m128 distance{};
		distance.m128_f32[0] = cameraPosition.m128_f32[1] - m_boundingSphere.Center.y;
		distance.m128_f32[1] = cameraPosition.m128_f32[0] - m_boundingSphere.Center.x;

		float rotation = atan2(distance.m128_f32[0], distance.m128_f32[1]);

		DirectX::XMMATRIX rotationMatrix = XMMatrixRotationZ(rotation + XM_PIDIV2);

		float length = XMVector2Length(distance).m128_f32[0];

		rotationMatrix = rotationMatrix * XMLoadFloat4x4(&m_worldMatrix);
		XMFLOAT4X4 shadowMatrix;
		XMStoreFloat4x4(&shadowMatrix, rotationMatrix);
		shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.SetShaderParameters(deviceContext, shadowMatrix, viewMatrix, projectionMatrix);
		shader.SetShaderColorParameters(deviceContext, m_colorFilter);
		m_vertexBuffer->Render(deviceContext);

		//shader.shadow->End(deviceContext);
		//shader.standard->Begin(deviceContext);
	}
}

void Tree::Update(const float dt)
{
	m_flags.m_rendering = validateRendering(m_boundingSphere.Center);
	if (m_flags.m_rendering)
	{
		DirectX::XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(m_boundingSphere.Center.x, m_boundingSphere.Center.y, m_boundingSphere.Center.z));
	}
}

void Tree::SetZ(const float z)
{
	m_boundingSphere.Center.z = z;
}

void Tree::Release()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

int32 Tree::isReleased() const noexcept
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

void Tree::Intersect( class EObject* const other)
{

}

const RenderLayerType Tree::GetLayerType() const noexcept
{
	return RenderLayerType::ENUM_OBJECT_TYPE;
}

void Tree::Remove()
{
	class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
	action->push(new ActionRemoveObject(this));
	Timer::CreateInstantTimer(action);
}

void Tree::CastShadow(const bool shadow)
{
	m_flags.m_cast_shadow = shadow;
}

void Tree::SetVector(const DirectX::XMFLOAT3& vec) noexcept
{

}

DirectX::XMFLOAT3 Tree::GetVector() noexcept
{
	return { 0.f,0.f,0.f };
}

void Tree::SetStance(const modern_Boolean stance) noexcept
{
	m_stance = stance;
}

const modern_Boolean Tree::GetStance() const noexcept
{
	return m_stance;
}

void Tree::SetGlobal(class Global * const global) noexcept
{
	m_global = global;
}

RenderHandle Tree::GetRenderHandle()
{
	return RenderHandle(m_texture,m_vertexBuffer);
}
