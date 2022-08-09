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
		class Shader* const interfaceShader,
		class Shader* const textShader,
		WCHAR* paths,
		const XMFLOAT3 position,
		const float xsize,
		const float ysize,
		const enum ObjectAnchorType anchor
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
	void RemoveNow() override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	void Release() override;
	int32 isReleased() const modern_except_state override;
	void  Intersect( class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const modern_except_state override;
	void SetParent(class Interface* const parent);
	void SetBehavior(class IInterfaceBehavior* const behavior);
	void SetOffset(DirectX::XMFLOAT3 offset);
	void SetPosition(const struct DirectX::XMFLOAT3& position);
	void _vectorcall SetPosition(DirectX::FXMVECTOR& position);
	class IInterfaceBehavior* const GetBehavior();
	void PushChild(class EObject* const child);
	void SetText(std::string text, const float size);
	void SetText(class modern_string& text, const float size);
	class Interface* const GetParent() const modern_except_state;

	void SetVector(const DirectX::XMFLOAT3& vec) modern_except_state override;
	DirectX::XMFLOAT3 GetVector() modern_except_state override;

	void Show(const modern_Boolean value = modern_true) modern_except_state;

	friend class InterfaceButtonBehavior;
	friend class InterfaceCheckboxBehavior;
	friend class InterfaceSliderBehavior;
	friend class InterfaceStatusBarBehavior;

private:
	class Interface* m_parent;
	class IInterfaceBehavior* m_behavior;
	modern_array<class EObject*> m_children;

	DirectX::BoundingBox m_box;//??
	DirectX::XMFLOAT3 m_offset;

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT4X4    m_worldMatrix;
	XMFLOAT2      m_scale;
	float         m_size;

	float m_width;
	float m_height;

	Texture* m_texture;
	Text* m_text;
	VertexBuffer* m_vertexBuffer;

	
};

