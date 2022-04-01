#pragma once
#include "RenderContainer.h"
#include "Texture.h"
#include "ColorFilter.h"
#include "ModelVariant.h"

class npc : public EObject, public ColorFilter
{
public:
	int32 isReleased() const noexcept override;

	npc();

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
	const enum class RenderLayerType GetLayerType() const noexcept override;

private:

	struct ModelVariant m_variant;

	float               m_animationSpeed;
	float               m_currentSpeed;
	float               m_framesPerSecond;
};

