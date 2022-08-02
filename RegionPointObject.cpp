#include "RegionPointObject.h"

int32 RegionPointObject::isReleased() const modern_except_state
{
	return 0;
}

void _fastcall RegionPointObject::Render(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{

}

void _fastcall RegionPointObject::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void RegionPointObject::Update(const float dt)
{
}

void RegionPointObject::SetZ(const float z)
{
}

void RegionPointObject::Release()
{
}

void RegionPointObject::Intersect( EObject* const other)
{
}
