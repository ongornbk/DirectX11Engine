#pragma once
#include "Shader.h"


class VertexBuffer
{
public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 uv;
	};

	VertexBuffer(void);
	~VertexBuffer(void);

	bool Initialize(ID3D11Device* device, Shader* shader, float size[2], bool writeable = false);
	bool InitializePart(ID3D11Device* device, Shader* shader, float size[2],float coords[6], bool writeable = false);
	void Render(ID3D11DeviceContext* deviceContext);
	bool ResizeTexture(ID3D11Device * device, float size, bool writeable = false);

	VertexType* GetVertices();
	ID3D11Buffer* GetVertexBuffer();
	int GetIndexCount();
	int GetVertexCount();
protected:
private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	VertexType* m_vertices;
	Shader* m_shader;
};

