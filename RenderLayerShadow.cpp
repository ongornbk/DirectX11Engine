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
	//#pragma omp parallel
	{
		m_size = 0ull;
		for (int32_t i = 0; i < MAP_DIVISION; ++i)
		{
			m_size += m_objects[1][i].size();
		}
	}

	//#pragma omp for schedule(dynamic)
	for (int32_t i = 0; i < MAP_DIVISION; ++i)
	{
		if (!xta[i])
			for (auto& obj : m_objects[1][i])
			{
				if (obj)
				{
					//modern_guard objG(obj);
					obj->Update(dt);
				}
			}
	}
	//#pragma omp barrier
}

void RenderLayerShadow::CleanUp()
{
	__CleanUp(m_objects[1]);
}

void _stdcall RenderLayerShadow::Sort()
{
	SortByXV(m_objects);
	SortByYV(m_objects);
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
	class modern_array<class modern_array<class EObject*>*> mvpp;


	for (int32 i = 0; i < MAP_DIVISION; i++)
	{
		if (!yta[i])
			mvpp.push_back(&m_objects[1][i]);
	}

	std::reverse(mvpp.begin(), mvpp.end());

	uint32 group = MAP_DIVISION - 1;
	for (auto& vec : mvpp)
	{
		GRAPHICS EnableAlphaBlending(true);

		shader.BeginShadow();

		modern_array_iterator<EObject*> mbpi(*vec);

		for (auto& obj : mbpi)
		{
			obj->PreRender(deviceContext, viewMatrix, projectionMatrix, shader);
		}

		GRAPHICS EnableAlphaBlending(false);


		//shader.End();
		shader.BeginStandard();

		uint32 index = 0u;
		for (auto& obj : mbpi)
		{
			obj->Render(deviceContext, viewMatrix, projectionMatrix, shader);
			obj->m_index = index;
			obj->m_vector = group;
			index++;
		}
		group--;
	}
}

void _vectorcall RenderLayerShadow::PreRender(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) noexcept
{
}

void RenderLayerShadow::Clear()
{
	for (int32 cv = 0; cv < MAP_DIVISION; cv++)
	{
		for (auto&& agent : m_objects[0][cv])
		{
			if (agent)
			{
				agent->Release();
				agent = nullptr;
			}
		}
		m_objects[0][cv].clear();
		m_objects[1][cv].clear();
	}
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
	m_objects[1][0].push_back(object);
}

void RenderLayerShadow::Push(Interface* const inter)
{
}

std::stack<class Unit*> _vectorcall RenderLayerShadow::GetUnitsInRange(Unit* object, float range) noexcept
{
	return std::stack<class Unit*>();
}

std::stack<class Unit*> _vectorcall RenderLayerShadow::GetUnitsInRange(Agent* agent, float range) noexcept
{
	return std::stack<class Unit*>();
}

std::stack<class Tree*> _vectorcall RenderLayerShadow::GetTreesBelow(class EObject* const object, float range) noexcept
{
	return std::stack<class Tree*>();
}
