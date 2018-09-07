#include "AnimatedSprite.h"
#include "Onion.h"
#include "Engine.h"

using Onion::Timer;

AnimatedSprite::AnimatedSprite(float size, float framesPerSecond, float animationSpeed, bool isLooping) : Sprite(size)
{
	m_framesPerSecond = (1000.0f / framesPerSecond) / 1000.0f;
	m_animationSpeed = animationSpeed;
	m_isLooping = isLooping;
	m_currentSpeed = 0;
}




AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Initialize(ID3D11Device * device, ID3D11DeviceContext* deviceContext, Shader * shader, WCHAR* textureFileName)
{
	Sprite::Initialize(device, shader, textureFileName, true);

	m_deviceContext = deviceContext;
	m_currentFrame = 0;
	m_previousFrame = -1.0f;
	m_maxFrames = (float)m_texture->GetWidth() / ((float)m_texture->GetHeight());
}



void AnimatedSprite::Update()
{
	if (m_maxFrames == 1.0f) return;
	if (m_currentFrame < m_maxFrames)
	{
		float dt = Timer::GetDeltaTime();
		m_currentSpeed += m_animationSpeed + dt;

		if (m_currentSpeed > m_framesPerSecond)
		{
			m_currentFrame++;
			m_currentSpeed = 0.0f;
			if (m_currentFrame >= m_maxFrames)
			{
				if (m_isLooping)
				{
					m_currentFrame = 0.0f;
				}
				else
				{
					m_currentFrame = m_maxFrames;
				}
			}

		}
	}
	if (m_currentFrame == m_previousFrame) return;
	
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

void AnimatedSprite::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	
	Sprite::Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	

}

void AnimatedSprite::SetAnimationSpeed(float speed)
{
	m_animationSpeed = speed;
}
