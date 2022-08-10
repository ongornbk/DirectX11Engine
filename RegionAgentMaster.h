#pragma once
#include "RenderContainer.h"
#include "IRegionAgent.h"
#include "Text.h"

class RegionAgentMaster : public EObject
{
	class EObject* m_intersectA;
	class EObject* m_intersectB;
	enum class AgentIntersectStance m_intersectStance;

	modern_handle m_parent;

	Text* m_text = nullptr;

	XMFLOAT4X4    m_worldMatrix;

public:
	RegionAgentMaster();
	~RegionAgentMaster();

	void Initialize(
		const XMFLOAT2 position,
		class Region* const agent
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
	void PostInitializeText();

	void SetVector(const DirectX::XMFLOAT3& vec) modern_except_state override;
	DirectX::XMFLOAT3 GetVector() modern_except_state override;

	void SetText(std::string text);
};