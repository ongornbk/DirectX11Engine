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
	
	_Use_decl_annotations_
	void _fastcall Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
		const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;

	_Use_decl_annotations_
	void _fastcall PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
		const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void Update(const float dt) override;
	void SetZ(const float z = 0.0f) override;
	void Release() override;
	int32 isReleased() const noexcept override;
	void _stdcall Intersect(class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const noexcept override;

	void SetNumberOfFrames(const float frames);

private:

	bool m_destroyed;

	struct ID3D11DeviceContext* m_deviceContext;

	struct DirectX::XMFLOAT3      m_lastPosition;

	struct DirectX::XMFLOAT4X4    m_worldMatrix;
	float         m_size;

	class Texture*      m_texture;
	class VertexBuffer* m_vertexBuffer;

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
