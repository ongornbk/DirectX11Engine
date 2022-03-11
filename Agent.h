#pragma once
#include "RenderContainer.h"
#include "AgentIntersectStance.h"

/*
* https://allegro.pl/oferta/zasilacz-samsung-bn44-00623b-l46x1q-dhs-ue46f6800-11907269263
*/

class Agent : public EObject
{
	class EObject* m_intersectA;
	class EObject* m_intersectB;
	enum class AgentIntersectStance m_intersectStance;

public:
	Agent();
	~Agent();

	void Initialize(
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
	int32 isReleased() const noexcept override;
	void Intersect(class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const noexcept override;
	void Remove() override;

	void SetVector(const DirectX::XMFLOAT3& vec) noexcept override;
	DirectX::XMFLOAT3 GetVector() noexcept override;
};
