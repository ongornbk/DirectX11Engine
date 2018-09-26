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

	Center = XMFLOAT3(POSITION_ZERO_POINT_X, POSITION_ZERO_POINT_Y, POSITION_ZERO_POINT_Z);
	Radius = COLLISION_DISABLED_OR_NULL;
	m_flags[0] = TRUE;//rendering
	m_flags[1] = FALSE;//selected
	m_flags[2] = TRUE;//pushable
	m_flags[3] = FALSE;//blocked
	m_flags[4] = FALSE;//collision with tilemap
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

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

void AnimatedDoodads::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR * paths, float size, float collision, XMFLOAT3 position, bool pushable)
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


	m_flags[2] = pushable;

	Radius = collision;
	Center = position;
	Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix
	Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix

	m_type = RenderContainer::RenderContainerType::ANIMATED_DOODADS;
}

void AnimatedDoodads::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader * shader)
{
	if (m_flags[0] && m_texture)
	{
		shader->SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);
	}
}

void AnimatedDoodads::Update(float dt)
{

	m_flags[0] = validateRendering(Center);
	if (m_flags[0])
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
		XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y + (m_size / 1.5f), Center.z - (m_size / 1.5f)));
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

void AnimatedDoodads::SetZ(float z)
{
	Center.z = z;
}

BoundingSphere * AnimatedDoodads::GetBoundingSphere()
{
	return (BoundingSphere*)(this);
}

void AnimatedDoodads::Release()
{
	delete this;
}

bool AnimatedDoodads::Flag(uint8_t index)
{
	return m_flags[index];
}

void AnimatedDoodads::Flag(uint8_t index, bool boolean)
{
	m_flags[index] = boolean;
}

void AnimatedDoodads::SetNumberOfFrames(float frames)
{
	m_maxFrames = frames;
}
