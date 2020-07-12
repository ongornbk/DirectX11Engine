#pragma once
#include "Shader.h"
#include "Vertex.h"
#include "ObjectAnchorType.h"

class VertexBuffer
{
public:
	

	VertexBuffer(void);
	~VertexBuffer(void);

	bool Initialize(ID3D11Device* device, Shader* shader, float size[2], bool writeable = false);
	bool InitializeAnchorBottom(ID3D11Device* device, Shader* shader, float size[2], bool writeable = false);
	bool InitializePart(ID3D11Device* device, Shader* shader, float size[2],float coords[6], bool writeable = false);
	void _stdcall Render(struct ID3D11DeviceContext* const deviceContext) noexcept;
	bool ResizeTexture(ID3D11Device * device, float size, bool writeable = false);
	void SetAnchor(const enum ObjectAnchorType type) noexcept;
	void SetNumberOfElements(const int32 elements = 1) noexcept;

	SpriteVertexType* GetVertices();
	ID3D11Buffer* GetVertexBuffer();
	int GetIndexCount();
	int GetVertexCount();
protected:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	Shader* m_shader;
private:

	SpriteVertexType* m_vertices;
	ObjectAnchorType  m_anchorType;
	int32_t           m_numOfElements;
};

