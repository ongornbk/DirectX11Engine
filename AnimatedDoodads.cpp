#include "AnimatedDoodads.h"
#include "RendererManager.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "GPUMemory.h"
#include "modern/modern_guard.h"
#include "Timer.h"
#include "IPP.h"

#define STANDARD_FRAMES 1.0f

AnimatedDoodads::AnimatedDoodads()
{
	m_destroyed = false;
	m_maxFrames = STANDARD_FRAMES;
	m_previousFrame = 0.f;
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	m_boundingSphere.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_boundingSphere.Radius = 0.0f;
	m_lastPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

	m_currentFrame = 0.f;
	m_stopped = false;
	m_isLooping = true;
	m_animationSpeed = 30.0f;
	m_framesPerSecond = 1.0f;
	m_currentSpeed = 0.0f;
	m_previousSpeed = 0.f;
	m_stop = false;
	m_rotations = 1.0f;
	m_size = 0.f;

	m_type_v2 = (struct GameObjectTypeInterface*)GAMEOBJECT_TYPE_ANIMATED_DOODADS_INFO;
}


AnimatedDoodads::~AnimatedDoodads()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void AnimatedDoodads::Initialize(
	struct ID3D11Device * const device,
	struct ID3D11DeviceContext * const deviceContext,
	class Shader * const shader,
	WCHAR * paths,
	const float size,
	const float collision,
	const struct DirectX::XMFLOAT3 position
	)
{
	m_size = size;


	m_vertexBuffer = new class VertexBuffer();
	float sizexy[2] = { m_size,m_size};
	(void)m_vertexBuffer->InitializeAnchorBottom(device, shader, sizexy, true);

	if (paths != NULL)
	{
		std::wstring tmp0 = std::wstring(paths);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	m_deviceContext = deviceContext;

	m_boundingSphere.Radius = collision;
	m_boundingSphere.Center = position;

	m_type = GameObjectType::OBJECT_TYPE_ANIMATED_DOODADS;
}

void AnimatedDoodads::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct DirectX::XMFLOAT4X4& viewMatrix,
	const struct DirectX::XMFLOAT4X4& projectionMatrix,
	const struct ShaderPackage &shader
)
{
	if (m_flags.m_rendering)
	{
		shader.BeginStandard();
		shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);
	}
}

void AnimatedDoodads::PreRender(
	struct ID3D11DeviceContext * const deviceContext,
	const struct DirectX::XMFLOAT4X4 & viewMatrix,
	const struct DirectX::XMFLOAT4X4 & projectionMatrix,
	const struct ShaderPackage & shader
)
{

}

void AnimatedDoodads::Update(float dt)
{

	m_flags.m_rendering = validateRendering(m_boundingSphere.Center);
	if (m_flags.m_rendering)
	{
		if (m_currentFrame < m_maxFrames)
		{
			m_currentSpeed += m_animationSpeed * dt;

			if (m_currentSpeed > m_framesPerSecond)
			{
				m_currentFrame++;
				m_currentSpeed = 0.f;
				if (m_currentFrame >= m_maxFrames)
				{
					if (m_isLooping)
					{
						m_currentFrame = 0.0f;
					}
					else
					{
						m_currentFrame = 0.0f;
						m_previousFrame = -1.0f;
					}
				}

			}
		}


		if (m_currentFrame == m_previousFrame) return;
		XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(m_boundingSphere.Center.x, m_boundingSphere.Center.y + (m_size / 1.5f), m_boundingSphere.Center.z - (m_size / 1.5f)));
	}



	D3D11_MAPPED_SUBRESOURCE mappedResource;
	SpriteVertexType* vertices = m_vertexBuffer->GetVertices();

	vertices[0].uv.x = m_currentFrame / m_maxFrames;
	vertices[0].uv.y = 1.0f;

	vertices[1].uv.x = m_currentFrame / m_maxFrames;
	vertices[1].uv.y = 0.0f;

	vertices[2].uv.x = (m_currentFrame + 1.0f) / m_maxFrames;
	vertices[2].uv.y = 0.0f;

	vertices[3].uv.x = (m_currentFrame + 1.0f) / m_maxFrames;
	vertices[3].uv.y = 1.0f;


	{
		modern_guard g(GPUMemory::get());
		HRESULT result = m_deviceContext->Map(m_vertexBuffer->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			return;
		}

		SpriteVertexType* verticesPtr = (SpriteVertexType*)mappedResource.pData;
		memcpy(verticesPtr, (void*)vertices, sizeof(SpriteVertexType) * m_vertexBuffer->GetVertexCount());
		m_deviceContext->Unmap(m_vertexBuffer->GetVertexBuffer(), 0);
	}
	m_previousFrame = m_currentFrame;

}

void AnimatedDoodads::SetZ(const float z)
{
	m_boundingSphere.Center.z = z;
}

void AnimatedDoodads::Release()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

int32 AnimatedDoodads::isReleased() const modern_except_state
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

void AnimatedDoodads::Intersect( class GameObject* const other)  
{

}

const RenderLayerType AnimatedDoodads::GetLayerType() const modern_except_state
{
	if (m_destroyed)
		return RenderLayerType::ENUM_OBJECT_TYPE;
	return RenderLayerType::ENUM_OBJECT_TYPE;
}

void AnimatedDoodads::Remove()
{
	safe_remove();
}

void AnimatedDoodads::RemoveNow()
{
	m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DELETE;
}

void AnimatedDoodads::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{

}

DirectX::XMFLOAT3 AnimatedDoodads::GetVector() modern_except_state
{
	return { 0.f,0.f,0.f };
}

void AnimatedDoodads::SetNumberOfFrames(float frames)
{
	m_maxFrames = modern_max(1.f,frames);
}