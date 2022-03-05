#pragma once
#include "RenderContainer.h"
#include "ColorFilter.h"
#include "RenderLayerType.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "IInterfaceBehavior.h"
#include "modern/modern_array.h"
#include "Text.h"

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
		const XMFLOAT3 position,
		const float xsize,
		const float ysize
	);

	void PostInitializeText();

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
	void  Intersect( class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const noexcept override;
	void SetParent(class Interface* const parent);
	void SetBehavior(class IInterfaceBehavior* const behavior);
	void SetOffset(DirectX::XMFLOAT3 offset);
	void SetPosition(const struct DirectX::XMFLOAT3& position);
	void _vectorcall SetPosition(DirectX::FXMVECTOR& position);
	class IInterfaceBehavior* const GetBehavior();
	void PushChild(class EObject* const child);
	void SetText(std::string text);
	void SetText(class modern_string& text);
	class Interface* const GetParent() const noexcept;

	void SetVector(const DirectX::XMFLOAT3& vec) noexcept override;
	DirectX::XMFLOAT3 GetVector() noexcept override;

	friend class InterfaceButtonBehavior;
	friend class InterfaceCheckboxBehavior;
	friend class InterfaceSliderBehavior;

private:
	class Interface* m_parent;
	class IInterfaceBehavior* m_behavior;
	modern_array<class EObject*> m_children;

	DirectX::BoundingBox m_box;//??
	DirectX::XMFLOAT3 m_offset;

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT4X4    m_worldMatrix;
	float         m_size;

	Texture* m_texture;
	Text* m_text;
	VertexBuffer* m_vertexBuffer;
};

