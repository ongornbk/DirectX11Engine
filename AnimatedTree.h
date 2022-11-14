#pragma once

#include "Global.h"
#include "RenderHandle.h"
#include "ColorFilter.h"
#include "RegionC.h"

class AnimatedTree : public GameObject, public ColorFilter
{
public:
	AnimatedTree();
	~AnimatedTree();

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
			const struct _In_ XMFLOAT4X4& viewMatrix,
			const struct _In_ XMFLOAT4X4& projectionMatrix,
			const struct ShaderPackage& shader
		) override;

	_Use_decl_annotations_
		void _fastcall PreRender(
			struct ID3D11DeviceContext* const deviceContext,
			const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
			const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
			const struct ShaderPackage& shader
		) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	void Release() override;
	int32 isReleased() const modern_except_state override;
	void Intersect(class GameObject* const other) override;
	const enum class RenderLayerType GetLayerType() const modern_except_state override;
	void Remove() override;
	void RemoveNow() override;
	void CastShadow(const bool shadow = true);

	void SetVector(const DirectX::XMFLOAT3& vec) modern_except_state override;
	DirectX::XMFLOAT3 GetVector() modern_except_state override;

	void SetStance(const modern_Boolean stance) modern_except_state;
	const modern_Boolean GetStance() const modern_except_state;

	static void SetGlobal(class Global* global) modern_except_state;

	RenderHandle GetRenderHandle();

private:

	modern_handle m_fadeRegion;

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3       m_lastPosition;

	XMFLOAT4X4     m_worldMatrix;
	float          m_size;
	modern_Boolean m_stance;//Maybe enum class

	Texture* m_texture;
	VertexBuffer* m_vertexBuffer;

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


	inline void enable() modern_except_state;
	inline void disable() modern_except_state;
};