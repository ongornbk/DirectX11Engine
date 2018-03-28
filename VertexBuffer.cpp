#include "VertexBuffer.h"
#include "GlobalUtilities.h"


VertexBuffer::VertexBuffer()
{
	m_vertices = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_shader = 0;
}


VertexBuffer::~VertexBuffer()
{
	if (m_vertices)
	{
		delete m_vertices;
		m_vertices = NULL;
	}
	if (m_vertexBuffer)
	{
		(void)m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
	if (m_indexBuffer)
	{
		(void)m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}
}

bool VertexBuffer::Initialize(ID3D11Device * device, Shader * shader, float size[2], bool writeable)
{
	m_shader = shader;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new VertexType[m_vertexCount];
	indices = new unsigned long[m_indexCount];

	float halfSizex = size[0] / 2.0f;
	float halfSizey = size[1] / 2.0f;

	m_vertices[0].position = XMFLOAT3(-halfSizex, -halfSizey, 0.0f);
	m_vertices[0].uv = XMFLOAT2(0.0f,1.0f);

	m_vertices[1].position = XMFLOAT3(-halfSizex, halfSizey, 0.0f);
	m_vertices[1].uv = XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = XMFLOAT3(halfSizex, halfSizey, 0.0f);
	m_vertices[2].uv = XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = XMFLOAT3(halfSizex, -halfSizey, 0.0f);
	m_vertices[3].uv = XMFLOAT2(1.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = (writeable) ? D3D11_CPU_ACCESS_WRITE : 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] indices;

	
	
	return true;
}

void VertexBuffer::Render(ID3D11DeviceContext * deviceContext)
{
	//m_shader->Begin(deviceContext, 0);
	unsigned int stride, offset;

	stride = sizeof(VertexType);
	offset = 0;
	

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(m_indexCount, 0, 0);

}

bool VertexBuffer::ResizeTexture(ID3D11Device * device, float size, bool writeable)
{

	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new VertexType[m_vertexCount];
	indices = new unsigned long[m_indexCount];

	float halfSize = size / 2.0f;

	m_vertices[0].position = XMFLOAT3(-halfSize, -halfSize, 0.0f);
	m_vertices[0].uv = XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = XMFLOAT3(-halfSize, halfSize, 0.0f);
	m_vertices[1].uv = XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = XMFLOAT3(halfSize, halfSize, 0.0f);
	m_vertices[2].uv = XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = XMFLOAT3(halfSize, -halfSize, 0.0f);
	m_vertices[3].uv = XMFLOAT2(1.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = (writeable) ? D3D11_CPU_ACCESS_WRITE : 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	vertexBufferDesc;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] indices;
	indices = 0;



	return true;
}

VertexBuffer::VertexType * VertexBuffer::GetVertices()
{
	return m_vertices;
}

ID3D11Buffer * VertexBuffer::GetVertexBuffer()
{
	return m_vertexBuffer;
}

int VertexBuffer::GetIndexCount()
{
	return m_indexCount;
}

int VertexBuffer::GetVertexCount()
{
	return m_vertexCount;
}
