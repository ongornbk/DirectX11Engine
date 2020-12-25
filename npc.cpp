#include "npc.h"

int32 npc::isReleased() const noexcept
{
	if (m_managementType == ObjectManagementType::OBJECT_MANAGEMENT_DELETE)
		return true;
	return false;
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

void _cdecl npc::Intersect(EObject* const other)
{

}

const RenderLayerType npc::GetLayerType() const noexcept
{
	return RenderLayerType::ENUM_OBJECT_TYPE;
}
