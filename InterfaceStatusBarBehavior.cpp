#include "InterfaceStatusBarBehavior.h"

#include "InterfaceCheckboxBehavior.h"
#include "UserInterface.h"
#include "LUAManager.h"
#include "Options.h"
#include "GPUMemory.h"
#include "modern/modern_guard.h"

InterfaceStatusBarBehavior::InterfaceStatusBarBehavior(Interface* const inter) :
	m_owner(inter), m_status(1.f)
{

}

InterfaceStatusBarBehavior::~InterfaceStatusBarBehavior()
{

}

void InterfaceStatusBarBehavior::OnHover()
{
	
}

void InterfaceStatusBarBehavior::OnClick()
{

	
}

void InterfaceStatusBarBehavior::SetStatusScaleX(const float status)
{
	m_status = status;
	m_owner->m_scale.x = status;

	
}



void InterfaceStatusBarBehavior::SetStatusCutYAnchorBottom(const float status)
{
	m_status = status;

	struct D3D11_MAPPED_SUBRESOURCE mappedResource;
	struct SpriteVertexType* vertices = m_owner->m_vertexBuffer->GetVertices();

	vertices[2].uv.y = status;
	vertices[2].uv.x = 0.f;
	vertices[3].uv.y = 0.f;
	vertices[3].uv.x = 0.f;
	vertices[0].uv.y = 0.f;
	vertices[0].uv.x = 1.f;
	vertices[1].uv.y = status;
	vertices[1].uv.x = 1.f;

	vertices[0].position = DirectX::XMFLOAT3(-m_owner->m_box.Extents.x, 0.0f, 0.0f);
	vertices[1].position = DirectX::XMFLOAT3(-m_owner->m_box.Extents.x, m_owner->m_height * status, 0.0f);
	vertices[2].position = DirectX::XMFLOAT3(m_owner->m_box.Extents.x, m_owner->m_height * status, 0.0f);
	vertices[3].position = DirectX::XMFLOAT3(m_owner->m_box.Extents.x, 0.0f, 0.0f);

	{
		modern_guard g(GPUMemory::get());
		HRESULT result = Engine::GetEngine()->GetGraphics()->GetDeviceContext()->Map(m_owner->m_vertexBuffer->GetVertexBuffer(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
		if (FAILED(result))
		{
			//return;
			//goto EXIT_CRT_0;
		}
		else
		{
			struct SpriteVertexType* const verticesPtr = (struct SpriteVertexType* const)mappedResource.pData;
			memcpy(verticesPtr, (void*)vertices, sizeof(struct SpriteVertexType) * m_owner->m_vertexBuffer->GetVertexCount());
			Engine::GetEngine()->GetGraphics()->GetDeviceContext()->Unmap(m_owner->m_vertexBuffer->GetVertexBuffer(), 0);
		}
	}
}

void InterfaceStatusBarBehavior::SetStatusCutXAnchorLeft(const float status)
{
	m_status = status;

	struct D3D11_MAPPED_SUBRESOURCE mappedResource;
	struct SpriteVertexType* vertices = m_owner->m_vertexBuffer->GetVertices();

	vertices[0].uv.y = 1.f;
	vertices[0].uv.x = 0.f;
	vertices[1].uv.y = 0.f;
	vertices[1].uv.x = 0.f;
	vertices[2].uv.y = 0.f;
	vertices[2].uv.x = status;
	vertices[3].uv.y = 1.f;
	vertices[3].uv.x = status;

	vertices[0].position = DirectX::XMFLOAT3(0.f, -m_owner->m_box.Extents.y, 0.0f);
	vertices[1].position = DirectX::XMFLOAT3(0.f, m_owner->m_box.Extents.y, 0.0f);
	vertices[2].position = DirectX::XMFLOAT3(m_owner->m_width * status, m_owner->m_box.Extents.y, 0.0f);
	vertices[3].position = DirectX::XMFLOAT3(m_owner->m_width * status, -m_owner->m_box.Extents.y, 0.0f);

	//#pragma omp critical
	{
		modern_guard g(GPUMemory::get());
		HRESULT result = Engine::GetEngine()->GetGraphics()->GetDeviceContext()->Map(m_owner->m_vertexBuffer->GetVertexBuffer(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
		if (FAILED(result))
		{
			//return;
			//goto EXIT_CRT_0;
		}
		else
		{
			struct SpriteVertexType* const verticesPtr = (struct SpriteVertexType* const)mappedResource.pData;
			memcpy(verticesPtr, (void*)vertices, sizeof(struct SpriteVertexType) * m_owner->m_vertexBuffer->GetVertexCount());
			Engine::GetEngine()->GetGraphics()->GetDeviceContext()->Unmap(m_owner->m_vertexBuffer->GetVertexBuffer(), 0);
		}
	}
}

const InterfaceBehaviorType InterfaceStatusBarBehavior::GetType() const modern_except_state
{
	return InterfaceBehaviorType::INTERFACE_BEHAVIOR_TYPE_STATUSBAR;
}
