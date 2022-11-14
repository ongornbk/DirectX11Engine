#pragma once
#include "GameObject.h"
#include "VertexBuffer.h"
#include "Texture.h"


class Projectile : public GameObject
{
protected:
	modern_handle m_owner;

	float m_size;
	float m_collision;
	struct DirectX::XMFLOAT3 m_velocity;

	class VertexBuffer* m_vertexBuffer;
	class Texture* m_texture;
	struct DirectX::XMFLOAT4X4 m_worldMatrix;
public:
	Projectile();
	~Projectile();

	void Initialize(
		struct ID3D11Device* const device,
		struct ID3D11DeviceContext* const deviceContext,
		class Shader* const shader,
		WCHAR* path,
		const float size,
		const float collision,
		const struct DirectX::XMFLOAT3& position,
		const struct DirectX::XMFLOAT3& velocity,
		class Unit* const owner
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

	void SetVector(const DirectX::XMFLOAT3& vec) modern_except_state override;
	DirectX::XMFLOAT3 GetVector() modern_except_state override;

protected:

	void destroy() modern_except_state;
};
