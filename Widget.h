#pragma once
#include "Handle.h"
#include "WidgetAnchor.h"
#include "WidgetFlags.h"
#include "Texture.h"
#include "VertexBuffer.h"

class Widget :
	public Handle
{
	WidgetAnchor  m_anchor;
	WidgetFlags   m_flags;
	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;

	

public:

	virtual void            Update(const float dt = 0.f) = 0;
	virtual void            Release() = 0;
	virtual bool            isReleased() const modern_except_state = 0;

	_Use_decl_annotations_
		virtual void _fastcall            Render(
			struct _In_ ID3D11DeviceContext* const deviceContext,
			const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
			const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
			const struct _In_ ShaderPackage& shader
		) = 0;

	_Use_decl_annotations_
		virtual void _fastcall           PreRender(
			struct ID3D11DeviceContext* _In_ const deviceContext,
			const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
			const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
			const struct _In_ ShaderPackage& shader
		) = 0;
};

