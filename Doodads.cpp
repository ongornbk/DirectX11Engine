#include "Doodads.h"
#include "RendererManager.h"
#include "IPP.h"



Doodads::Doodads()
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	Center = XMFLOAT3(POSITION_ZERO_POINT_X, POSITION_ZERO_POINT_Y, POSITION_ZERO_POINT_Z);
	Radius = COLLISION_DISABLED_OR_NULL;
	m_flags[0] = TRUE;//rendering
	m_flags[1] = FALSE;//selected
	m_flags[2] = TRUE;//pushable
	m_flags[3] = FALSE;//blocked
	m_flags[4] = FALSE;//collision with tilemap
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
}

Doodads::~Doodads()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void Doodads::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR * paths, float size, float collision, XMFLOAT3 position,bool pushable)
{

	m_vertexBuffer = new VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);

	if (paths != NULL)
	{
		wstring tmp0 = wstring(paths);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	
	m_deviceContext = deviceContext;

	m_size = size;

	m_flags[2] = pushable;

	Radius = collision;
	Center = position;
	//Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix
	//Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix

	m_type = RenderContainer::RenderContainerType::DOODADS;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	SpriteVertexType* vertices = m_vertexBuffer->GetVertices();
	
	vertices[0].uv.x = 0.0f;
	vertices[0].uv.y = 1.0f;
	
	vertices[1].uv.x = 0.0f;
	vertices[1].uv.y = 0.0f;
	
	vertices[2].uv.x = 1.0f;
	vertices[2].uv.y = 0.0f;
	
	vertices[3].uv.x = 1.0f;
	vertices[3].uv.y = 1.0f;
	
	
	
	HRESULT result = m_deviceContext->Map(m_vertexBuffer->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return;
	}
	
	SpriteVertexType* verticesPtr = (SpriteVertexType*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, sizeof(SpriteVertexType) * m_vertexBuffer->GetVertexCount());
	m_deviceContext->Unmap(m_vertexBuffer->GetVertexBuffer(), 0);
	
	//ipp::Console::Println((uint32_t)ipp::memory_cast<uint64_t>(m_texture));

}

void Doodads::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader * shader)
{
	if (m_flags[0]&&m_texture)
	{
		shader->SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);
		//ipp::Console::Print("#");
	}
}

void Doodads::Update(float dt)
{

	m_flags[0] = validateRendering(Center);
	if (m_flags[0])
	{
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y, Center.z));
	}

	if (TileMap::CollisionAt(Center))
	{
		Center = m_lastPosition;
		if (TileMap::CollisionAt(Center))
		{
			m_flags[4] = true;
			m_flags[1] = true;
		}
		else
		{
			m_flags[4] = false;
			m_flags[1] = false;
		}
	}
	else
	{
		m_flags[4] = false;
		m_flags[1] = false;
	}
}

BoundingSphere * Doodads::GetBoundingSphere()
{
	return (BoundingSphere*)(this);
}

void Doodads::Release()
{
	delete this;
}

bool Doodads::Flag(uint8_t index)
{
	return m_flags[index];
}

void Doodads::Flag(uint8_t index, bool boolean)
{
	m_flags[index] = boolean;
}
