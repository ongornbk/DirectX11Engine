#pragma once
#include "Sprite.h"
#include "RenderContainer.h"

class AnimatedDoodads : public RenderContainer, public BoundingSphere
{
public:
	AnimatedDoodads();
	~AnimatedDoodads();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* paths, float size, float collision, XMFLOAT3 position, bool pushable);

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	BoundingSphere* GetBoundingSphere() override;
	void Release() override;
	bool Flag(uint8_t index) override;
	void Flag(uint8_t index, bool boolean) override;

	void SetNumberOfFrames(float frames);

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3      m_lastPosition;

	XMFLOAT4X4    m_worldMatrix;
	float         m_size;
	bool          m_flags[5];

	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;

	//Animated stuff

	float         m_previousSpeed;
	float         m_rotations;
	int           m_stopped;
	bool          m_stop;

	float m_currentFrame;
	float m_previousFrame;
	float m_maxFrames;


	float         m_animationSpeed;
	float         m_currentSpeed;
	float         m_framesPerSecond;
	bool          m_isLooping;
};
