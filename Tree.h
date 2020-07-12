#pragma once
#include "Sprite.h"
#include "RenderContainer.h"
#include "Global.h"
#include "RenderHandle.h"

class Tree : public EObject
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
	void _cdecl Intersect(class EObject* const other) override;

	static void SetGlobal(class Global* global) noexcept;

	RenderHandle GetRenderHandle();

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3      m_lastPosition;

	XMFLOAT4X4    m_worldMatrix;
	float         m_size;

	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;
};

