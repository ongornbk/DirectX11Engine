#pragma once
#include "RenderContainer.h"
#include "AgentIntersectStance.h"



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
	int32 isReleased() const modern_except_state override;
	void Intersect(class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const modern_except_state override;
	void Remove() override;
	void RemoveNow() override;

	void SetVector(const DirectX::XMFLOAT3& vec) modern_except_state override;
	DirectX::XMFLOAT3 GetVector() modern_except_state override;
};
