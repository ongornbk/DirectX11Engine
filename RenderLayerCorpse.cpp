#include "RenderLayerCorpse.h"

RenderLayerCorpse::RenderLayerCorpse()
{
}

RenderLayerCorpse::~RenderLayerCorpse()
{
}

const RenderLayerType RenderLayerCorpse::GetType() const noexcept
{
	return RenderLayerType::ENUM_CORPSE_TYPE;
}

void RenderLayerCorpse::Update(const float dt)
{
}

void RenderLayerCorpse::CleanUp()
{
}

void _stdcall RenderLayerCorpse::Sort()
{
}

void _stdcall RenderLayerCorpse::QSort()
{
}

void _stdcall RenderLayerCorpse::StaticSort()
{
}

void _stdcall RenderLayerCorpse::StaticQSort()
{
}

void _vectorcall RenderLayerCorpse::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) noexcept
{
}

void _vectorcall RenderLayerCorpse::PreRender(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) noexcept
{
}

void RenderLayerCorpse::Clear()
{
}

void RenderLayerCorpse::Push(Unit* const unit)
{
}

void RenderLayerCorpse::Push(Doodads* const doodads)
{
}

void RenderLayerCorpse::Push(AnimatedDoodads* const animated)
{
}

void RenderLayerCorpse::Push(Tree* const tree)
{
}

void RenderLayerCorpse::Push(RegionPointObject* const tree)
{
}

std::stack<class Unit*> _vectorcall RenderLayerCorpse::GetUnitsInRange(Unit* object, float range) noexcept
{
	return std::stack<class Unit*>();
}
