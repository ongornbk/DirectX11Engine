#pragma once
#include "AnimatedSprite.h"
#include "SpriteModel.h"

using namespace DirectX;

class Entity
{
public:
	friend class EntityManager;
	~Entity(void);

	void InitializeSprite(ID3D11Device* device,Shader* shader,WCHAR* textureFileName,float spriteSize);
	void InitializeAnimatedSprite(ID3D11Device* device,ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* textureFileName, float spriteSize,
		float framesPerSecond,float animationSpeed = 1.0f,bool isLooping = false);


	void Update();
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void ResizeTexture(float size);

	void SetPosition(float x = 0.0f, float y = 0.0f);
	void SetVelocity(float x = 0.0f, float y = 0.0f);
	void Translate(float x = 0.0f, float y = 0.0f);

	

private:
	Entity(void);
	XMFLOAT4X4  m_worldMatrix;
	XMVECTOR    m_position;
	XMVECTOR    m_velocity;
	Sprite*     m_sprite;

};

