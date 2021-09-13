#include "VertexBuffer.h"
#include "GlobalUtilities.h"
#include "IPP.h"
#include "Engine.h"
#include <mutex>
namespace
{
	static constexpr uint32 t_indices6[6] = { 0u,1u,2u,0u,2u,3u };
}

VertexBuffer::VertexBuffer()
{
	m_anchorType = ObjectAnchorType::OBJECT_ANCHOR_TYPE_CENTER;
	m_indexCount = 0;
	m_vertexBuffer = 0;
	m_vertices = nullptr;
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	m_shader = nullptr;
}


VertexBuffer::~VertexBuffer()
{
	if (m_vertices)
	{
		delete m_vertices;
		m_vertices = nullptr;
	}
	if (m_vertexBuffer)
	{
		(void)(m_vertexBuffer->Release());
		m_vertexBuffer = nullptr;
	}
	if (m_indexBuffer)
	{
		(void)(m_indexBuffer->Release());
		m_indexBuffer = nullptr;
	}

}

bool VertexBuffer::Initialize(ID3D11Device * device, Shader * shader, float size[2], bool writeable)
{
	m_shader = shader;
	uint32_t* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SpriteVertexType[m_vertexCount];
	indices = new uint32_t[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32_t) * 6);

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

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertexType)*m_vertexCount;
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

bool VertexBuffer::Initialize(VertexBuffer* const other)
{
	m_shader = other->m_shader;
	uint32_t* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	struct ID3D11Device* const device = Engine::GetEngine()->GetGraphics()->GetDevice();

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SpriteVertexType[m_vertexCount];
	indices = new uint32_t[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32_t) * 6);


	m_vertices[0].position = XMFLOAT3(other->m_vertices[0].position);
	m_vertices[0].uv = XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = XMFLOAT3(other->m_vertices[1].position);
	m_vertices[1].uv = XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = XMFLOAT3(other->m_vertices[2].position);
	m_vertices[2].uv = XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = XMFLOAT3(other->m_vertices[3].position);
	m_vertices[3].uv = XMFLOAT2(1.0f, 1.0f);

	vertexBufferDesc.Usage = (false) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = (false) ? D3D11_CPU_ACCESS_WRITE : 0;
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

bool VertexBuffer::InitializeAnchorBottom(
	struct ID3D11Device * const device,
	class Shader * const shader,
	float size[2],
	bool writeable)
{
	m_shader = shader;
	uint32_t* indices;
	struct D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	struct D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new struct SpriteVertexType[m_vertexCount];
	indices = new uint32_t[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32_t) * 6);

	float halfSizex = size[0] / 2.0f;

	m_vertices[0].position = DirectX::XMFLOAT3(-halfSizex, 0.0f, 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = DirectX::XMFLOAT3(-halfSizex, size[1], 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = DirectX::XMFLOAT3(halfSizex, size[1], 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = DirectX::XMFLOAT3(halfSizex, 0.0f, 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(struct SpriteVertexType)*m_vertexCount;
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

bool VertexBuffer::InitializeAnchorTopLeft(ID3D11Device* device, Shader* shader, float size[2], bool writeable)
{
	m_shader = shader;
	uint32_t* indices;
	struct D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	struct D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new struct SpriteVertexType[m_vertexCount];
	indices = new uint32_t[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32_t) * 6);

	float halfSizex = size[0] / 2.0f;

	m_vertices[0].position = DirectX::XMFLOAT3(0.f, -size[1], 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = DirectX::XMFLOAT3(0.f, 0.f, 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = DirectX::XMFLOAT3(size[0], 0.f, 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = DirectX::XMFLOAT3(size[0], -size[1], 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(struct SpriteVertexType) * m_vertexCount;
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

bool VertexBuffer::InitializeAnchorTopLeft(ID3D11Device* device, Shader* shader, DirectX::XMFLOAT2 size, bool writeable)
{
	m_shader = shader;
	uint32_t* indices;
	struct D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	struct D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new struct SpriteVertexType[m_vertexCount];
	indices = new uint32_t[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32_t) * 6);

	float halfSizex = size.x / 2.0f;

	m_vertices[0].position = DirectX::XMFLOAT3(0.f, -size.y, 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = DirectX::XMFLOAT3(0.f, 0.f, 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = DirectX::XMFLOAT3(size.x, 0.f, 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = DirectX::XMFLOAT3(size.x, -size.y, 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(struct SpriteVertexType) * m_vertexCount;
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

bool VertexBuffer::InitializePart(
	struct ID3D11Device * const device,
	class Shader * const shader,
	float size[2],
	float coords[6],
	bool writeable)
{
	m_shader = shader;
	uint32_t* indices;
	struct D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	struct D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new struct SpriteVertexType[m_vertexCount];
	indices = new uint32_t[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32_t) * 6);

	float halfSizex = size[0] / 2.0f;
	float halfSizey = size[1] / 1.0f;

	float width = coords[0];
	float height = coords[1];
	float left = coords[2];
	float top = coords[3];
	float right = coords[4];
	float bottom = coords[5];

	m_vertices[0].position = DirectX::XMFLOAT3(-halfSizex, -halfSizey, 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(left/width, bottom/height);

	m_vertices[1].position = DirectX::XMFLOAT3(-halfSizex, halfSizey, 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(left/width, top/height);

	m_vertices[2].position = DirectX::XMFLOAT3(halfSizex, halfSizey, 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(right/width,top/height);

	m_vertices[3].position = DirectX::XMFLOAT3(halfSizex, -halfSizey, 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(right/width, bottom/height);



	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(struct SpriteVertexType)*m_vertexCount;
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

void _stdcall VertexBuffer::Render(
	struct ID3D11DeviceContext * const deviceContext
) noexcept
{
	constexpr uint32 stride = sizeof(SpriteVertexType);
	constexpr uint32 offset = 0u;

	deviceContext->IASetVertexBuffers(0u, 1u, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(m_indexCount, 0u, 0);
}

bool VertexBuffer::ResizeTexture(
	struct ID3D11Device * const device,
	const float size,
	const bool writeable)
{
	uint32* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SpriteVertexType[m_vertexCount];
	indices = new uint32_t[m_indexCount];

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
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertexType)*m_vertexCount;
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

void VertexBuffer::SetAnchor(const enum ObjectAnchorType type) noexcept
{
	m_anchorType = type;
}

void VertexBuffer::SetNumberOfElements(const int32 elements) noexcept
{
	m_numOfElements = elements;
}

struct SpriteVertexType * VertexBuffer::GetVertices()
{
	return m_vertices;
}

struct ID3D11Buffer * VertexBuffer::GetVertexBuffer()
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
