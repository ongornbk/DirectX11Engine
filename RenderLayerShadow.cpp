#include "RenderLayerShadow.h"

RenderLayerShadow::RenderLayerShadow()
{
}

RenderLayerShadow::~RenderLayerShadow()
{
}

const RenderLayerType RenderLayerShadow::GetType() const noexcept
{
	return RenderLayerType::ENUM_SHADOW_TYPE;
}

void RenderLayerShadow::Update(const float dt)
{
}

void RenderLayerShadow::CleanUp()
{
}

void _stdcall RenderLayerShadow::Sort()
{
}

void _stdcall RenderLayerShadow::QSort()
{
}

void _stdcall RenderLayerShadow::StaticSort()
{
}

void _stdcall RenderLayerShadow::StaticQSort()
{
}

void _vectorcall RenderLayerShadow::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) noexcept
{
}

void _vectorcall RenderLayerShadow::PreRender(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) noexcept
{
}

void RenderLayerShadow::Clear()
{
}

void RenderLayerShadow::Push(Unit* const unit)
{
}

void RenderLayerShadow::Push(Doodads* const doodads)
{
}

void RenderLayerShadow::Push(AnimatedDoodads* const animated)
{
}

void RenderLayerShadow::Push(Tree* const tree)
{
}

void RenderLayerShadow::Push(RegionPointObject* const tree)
{
}

void RenderLayerShadow::Push(EObject* const object)
{
}

std::stack<class Unit*> _vectorcall RenderLayerShadow::GetUnitsInRange(Unit* object, float range) noexcept
{
	return std::stack<class Unit*>();
}

std::stack<class Tree*> _vectorcall RenderLayerShadow::GetTreesBelow(class EObject* const object, float range) noexcept
{
	return std::stack<class Tree*>();
}
