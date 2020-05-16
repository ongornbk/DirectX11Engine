#include "AnimatedDoodads.h"
#include "RendererManager.h"
#include "IPP.h"

#define STANDARD_FRAMES 1.0f

AnimatedDoodads::AnimatedDoodads()
{
	m_maxFrames = STANDARD_FRAMES;

	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	m_boundingSphere.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_boundingSphere.Radius = 0.0f;
	m_lastPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

	m_currentFrame = 0.f;
	m_isLooping = true;
	m_animationSpeed = 0.20f;
	m_framesPerSecond = 1.0f;
	m_currentSpeed = 0.0f;
	m_stop = false;
	m_rotations = 16.0f;
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

	m_type = EObject::EObjectType::ANIMATED_DOODADS;
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
		shader.standard->SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.standard->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
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
		if (m_currentFrame < 24.0f)
		{
			m_currentSpeed += m_animationSpeed + dt;

			if (m_currentSpeed > m_framesPerSecond)
			{
				m_currentFrame++;
				m_currentSpeed = 0.0f;
				if (m_currentFrame >= 24.0f)
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
					}
				}

			}
		}
		if (m_currentFrame == m_previousFrame) return;
		XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(m_boundingSphere.Center.x, m_boundingSphere.Center.y + (m_size / 1.5f), m_boundingSphere.Center.z - (m_size / 1.5f)));
	}



	D3D11_MAPPED_SUBRESOURCE mappedResource;
	SpriteVertexType* vertices = m_vertexBuffer->GetVertices();

	vertices[0].uv.x = m_currentFrame / 24.0f;
	vertices[0].uv.y = 1.0f;

	vertices[1].uv.x = m_currentFrame / 24.0f;
	vertices[1].uv.y = 0.0f;

	vertices[2].uv.x = (m_currentFrame + 1.0f) / 24.0f;
	vertices[2].uv.y = 0.0f;

	vertices[3].uv.x = (m_currentFrame + 1.0f) / 24.0f;
	vertices[3].uv.y = 1.0f;



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

int32 AnimatedDoodads::isReleased() const noexcept
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

void AnimatedDoodads::SetNumberOfFrames(float frames)
{
	m_maxFrames = frames;
}