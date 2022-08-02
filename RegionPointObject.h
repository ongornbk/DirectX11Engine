#pragma once
#include "RenderContainer.h"
class RegionPointObject :
	public EObject
{


public:

	int32 isReleased() const modern_except_state override;

	_Use_decl_annotations_
		void _fastcall Render(
			struct _In_ ID3D11DeviceContext* const deviceContext,
			const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
			const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
			const struct _In_ ShaderPackage& shader
		) override;

	_Use_decl_annotations_
		void _fastcall PreRender(
			struct ID3D11DeviceContext* const deviceContext,
			const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
			const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
			const struct ShaderPackage& shader
		) override;
	void Update(const float dt) override;
	void SetZ(const float z = 0.0f) override;
	void Release() override;
	void Intersect( class EObject* const other) override;

};

