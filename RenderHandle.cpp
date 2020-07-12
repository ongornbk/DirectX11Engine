#include "RenderHandle.h"

RenderHandle::RenderHandle(Texture* const texture, VertexBuffer* const vertexBuffer) : m_texture(texture), m_buffer(vertexBuffer)
{
}

RenderHandle::~RenderHandle()
{
	m_buffer = nullptr;
	m_texture = nullptr;
}

void RenderHandle::SetNumberOfElements(const int32 elements)
{
	if (m_buffer)
		m_buffer->SetNumberOfElements(elements);
}

void RenderHandle::SetAnchorType(const ObjectAnchorType type)
{
	if (m_buffer)
		m_buffer->SetAnchor(type);
}
