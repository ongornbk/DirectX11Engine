#include "Shadow.h"

void Shadow::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* paths, const float size, const float collision, const DirectX::XMFLOAT3 position, GameObject* const parent)
{
	m_type = GameObjectType::OBJECT_TYPE_SHADOW;
}

void _fastcall Shadow::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
	if (m_parent)
		m_parent->PreRender(deviceContext,viewMatrix,projectionMatrix,shader);
}

void _fastcall Shadow::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void Shadow::Update(float dt)
{

}

void Shadow::SetZ(float z)
{

}

void Shadow::Release()
{
}

int32 Shadow::isReleased() const modern_except_state
{
	if (m_managementType == ObjectManagementType::OBJECT_MANAGEMENT_DELETE)
		return true;
	return false;
}

void  Shadow::Intersect(
	 class GameObject* const other
) 
{

}

const RenderLayerType Shadow::GetLayerType() const modern_except_state
{
	return RenderLayerType::ENUM_SHADOW_TYPE;
}
