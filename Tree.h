#pragma once
#include "Sprite.h"
#include "RenderContainer.h"
#include "Global.h"
#include "RenderHandle.h"
#include "ColorFilter.h"

class Tree : public EObject, public ColorFilter
{
public:
	Tree();
	~Tree();

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
		const struct ShaderPackage &shader
	) override;

	_Use_decl_annotations_
	void _fastcall PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
		const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	void Release() override;
	int32 isReleased() const noexcept override;
	void Intersect(class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const noexcept override;
	void Remove() override;
	void CastShadow(const bool shadow = true);

	void SetVector(const DirectX::XMFLOAT3& vec) noexcept override;
	DirectX::XMFLOAT3 GetVector() noexcept override;

	void SetStance(const modern_Boolean stance) noexcept;
	const modern_Boolean GetStance() const noexcept;

	static void SetGlobal(class Global* global) noexcept;

	RenderHandle GetRenderHandle();

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3       m_lastPosition;

	XMFLOAT4X4     m_worldMatrix;
	float          m_size;
	modern_Boolean m_stance;//Maybe enum class

	Texture*       m_texture;
	VertexBuffer*  m_vertexBuffer;
};

