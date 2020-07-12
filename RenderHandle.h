#pragma once
#include "Texture.h"
#include "VertexBuffer.h"

class RenderHandle
{

	class Texture* m_texture;
	class VertexBuffer* m_buffer;

public:
	RenderHandle(
		class Texture* const texture,
		class VertexBuffer* const vertexBuffer);

	~RenderHandle();

	void SetNumberOfElements(const int32 elements);
	void SetAnchorType(const enum ObjectAnchorType type);
};

