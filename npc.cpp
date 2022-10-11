#include "npc.h"

int32 npc::isReleased() const modern_except_state
{
	if (m_managementType == ObjectManagementType::OBJECT_MANAGEMENT_DELETE)
		return true;
	return false;
}

npc::npc() : 
	ColorFilter(1.f,1.f,1.f,1.f),
	m_animationSpeed(30.f),
	m_framesPerSecond(1.f),
	m_currentSpeed(0.f)
{
	m_type = EObjectType::OBJECT_TYPE_NPC;
}

void _fastcall npc::Render(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{

}

void _fastcall npc::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{

}

void npc::Update(const float dt)
{

}

void npc::SetZ(const float z)
{

}

void npc::Release()
{

}

void npc::Intersect( GameObject* const other) 
{

}

const RenderLayerType npc::GetLayerType() const modern_except_state
{
	return RenderLayerType::ENUM_OBJECT_TYPE;
}
