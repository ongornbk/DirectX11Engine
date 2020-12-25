#pragma once
#include "RenderContainer.h"

class Shadow : public EObject
{
	class EObject* m_parent;

public:

	void Initialize(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		class Shader* shader,
		WCHAR* paths,
		const float size,
		const float collision,
		const struct DirectX::XMFLOAT3 position,
		class EObject* const parent
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
	int32 isReleased() const noexcept override;
	void _cdecl Intersect(class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const noexcept override;

};

