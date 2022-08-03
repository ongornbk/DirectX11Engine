#include "Doodads.h"
#include "RendererManager.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"
#include "IPP.h"


namespace
{
	static Global* m_global = nullptr;
}

Doodads::Doodads() : ColorFilter(1.f, 1.f, 1.f, 1.f)
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_boundingSphere.Radius = 0.0f;

	m_destroyed = false;

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

	m_vertexBuffer = new class VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);

	if (paths != NULL)
	{
		std::wstring tmp0 = std::wstring(paths);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	
	m_deviceContext = deviceContext;

	m_boundingSphere.Radius = collision;
	m_boundingSphere.Center = position;
	m_boundingSphere.Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	m_boundingSphere.Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;


	m_type = EObject::EObjectType::OBJECT_TYPE_DOODADS;

	

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
		shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		shader.SetShaderColorParameters(deviceContext, m_colorFilter);
		m_vertexBuffer->Render(deviceContext);
	}
}

void Doodads::PreRender(
	struct ID3D11DeviceContext * const deviceContext,
	const struct DirectX::XMFLOAT4X4 & viewMatrix,
	const struct DirectX::XMFLOAT4X4 & projectionMatrix,
	const struct ShaderPackage & shader
)
{
	if (m_flags.m_rendering)
	{
		if (m_flags.m_cast_shadow)
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
		DirectX::XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(m_boundingSphere.Center.x, m_boundingSphere.Center.y, m_boundingSphere.Center.z));
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

int32 Doodads::isReleased() const modern_except_state
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

void Doodads::Intersect( class EObject* const other) 
{
}

const RenderLayerType Doodads::GetLayerType() const modern_except_state
{
	if (m_destroyed)
		return RenderLayerType::ENUM_OBJECT_TYPE;
	return RenderLayerType::ENUM_OBJECT_TYPE;
}

void Doodads::Remove()
{
	safe_remove();
}

void Doodads::RemoveNow()
{
	m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DELETE;
}

void Doodads::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{
}

DirectX::XMFLOAT3 Doodads::GetVector() modern_except_state
{
	return { 0.f,0.f,0.f };
}
