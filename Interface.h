#pragma once
#include "RenderContainer.h"
#include "ColorFilter.h"
#include "RenderLayerType.h"
#include "Texture.h"
#include "VertexBuffer.h"

class Interface : public EObject, public ColorFilter
{
public:
	Interface();
	~Interface();

	void Initialize(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		class Shader* shader,
		WCHAR* paths,
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

	void Remove() override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	void Release() override;
	int32 isReleased() const noexcept override;
	void _cdecl Intersect(class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const noexcept override;

private:
	class Interface* m_parent;

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT4X4    m_worldMatrix;
	float         m_size;

	Texture* m_texture;
	VertexBuffer* m_vertexBuffer;
};

