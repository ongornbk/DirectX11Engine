#pragma once
#include "Sprite.h"
#include "RenderContainer.h"

class AnimatedDoodads : public EObject
{
public:
	AnimatedDoodads();
	~AnimatedDoodads();

	void Initialize(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		class Shader* shader,
		WCHAR* paths,
		const float size,
		const float collision,
		const XMFLOAT3 position
		);

	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	void Release() override;

	void SetNumberOfFrames(float frames);

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3      m_lastPosition;

	XMFLOAT4X4    m_worldMatrix;
	float         m_size;

	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;

	//Animated stuff

	float         m_previousSpeed;
	float         m_rotations;
	 int32           m_stopped;
	bool          m_stop;

	float m_currentFrame;
	float m_previousFrame;
	float m_maxFrames;


	float         m_animationSpeed;
	float         m_currentSpeed;
	float         m_framesPerSecond;
	bool          m_isLooping;
};
