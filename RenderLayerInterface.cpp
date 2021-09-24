#include "RenderLayerInterface.h"

RenderLayerInterface::RenderLayerInterface()
{
}
RenderLayerInterface::~RenderLayerInterface()
{
}

const RenderLayerType RenderLayerInterface::GetType() const noexcept
{
	return RenderLayerType::ENUM_INTERFACE_TYPE;

}

void RenderLayerInterface::Update(const float dt)
{
	m_size = 0u;
				if (m_root)
					m_root->Update(dt);
//#pragma omp barrier

}

void RenderLayerInterface::CleanUp()
{
	
}

void _stdcall RenderLayerInterface::Sort()
{
}

void _stdcall RenderLayerInterface::QSort()
{
}

void _stdcall RenderLayerInterface::StaticSort()
{
}

void _stdcall RenderLayerInterface::StaticQSort()
{
}

void _vectorcall RenderLayerInterface::Render(
	ID3D11DeviceContext* const deviceContext,
	const XMFLOAT4X4& viewMatrix,
	const XMFLOAT4X4& projectionMatrix,
	const ShaderPackage& shader)
	noexcept
{
	if (!m_root)
		return;

	

	//shader.BeginShadow();

	//m_root->PreRender(deviceContext, viewMatrix, projectionMatrix, shader);

	


	//shader.End();

	GRAPHICS EnableAlphaBlending(true);

	shader.BeginInterface();

	m_root->Render(deviceContext, viewMatrix, projectionMatrix, shader);

	GRAPHICS EnableAlphaBlending(false);

}

void _vectorcall RenderLayerInterface::PreRender(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) noexcept
{
}

void RenderLayerInterface::Clear()
{
	if (m_root)
	{
		m_root->Release();
		m_root = nullptr;
	}
}

void RenderLayerInterface::Push(Unit* const unit)
{
}

void RenderLayerInterface::Push(Doodads* const doodads)
{
}

void RenderLayerInterface::Push(AnimatedDoodads* const animated)
{
}

void RenderLayerInterface::Push(Tree* const tree)
{
}

void RenderLayerInterface::Push(RegionPointObject* const tree)
{
}

void RenderLayerInterface::Push(EObject* const object)
{

}

void RenderLayerInterface::Push(Interface* const inter)
{
	if (inter->GetParent() == nullptr)
		m_root = inter;
}

std::stack<class Unit*> _vectorcall RenderLayerInterface::GetUnitsInRange(Unit* object, float range) noexcept
{
	return std::stack<class Unit*>();
}

std::stack<class Tree*> _vectorcall RenderLayerInterface::GetTreesBelow(class EObject* const object, float range) noexcept
{
	return std::stack<class Tree*>();
}
