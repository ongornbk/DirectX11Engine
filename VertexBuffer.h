#pragma once
#include "Shader.h"
#include "Vertex.h"

class VertexBuffer
{
public:
	

	VertexBuffer(void);
	~VertexBuffer(void);

	bool Initialize(ID3D11Device* device, Shader* shader, float size[2], bool writeable = false);
	bool InitializePart(ID3D11Device* device, Shader* shader, float size[2],float coords[6], bool writeable = false);
	void Render(ID3D11DeviceContext* deviceContext);
	bool ResizeTexture(ID3D11Device * device, float size, bool writeable = false);

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
};

