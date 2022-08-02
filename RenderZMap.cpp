#include "RenderZMap.h"
#include "GarbageCollector.h"
#include "RenderContainerVector.h"
#include <map>

RenderZMap::RenderZMap()
{
	ZeroMemory(&m_zStance, sizeof(bool) * 256);
	m_fps = 60;
	m_sortingDepth = 1;
}

RenderZMap::~RenderZMap()
{
	for (auto vector : m_zVectors)
	{
		vector.second->Clear();
		delete vector.second;
		m_zStance[vector.first] = false;
	}
	m_zVectors.clear();
}

void RenderZMap::UpdateFps(const int32 fps)
{
	m_fps = fps;
}

void RenderZMap::Update(const float dt)
{
//#pragma omp parallel
	{
		for (auto vector : m_zVectors)
		{
			vector.second->Update(dt);
		}
	}
}

void RenderZMap::CleanUp()
{
//#pragma omp parallel
	for (auto vector : m_zVectors)
	{
		vector.second->CleanUp();
	}
}

void RenderZMap::Sort()
{

//#pragma omp parallel
	//std::map<int64,EObjectVector*>::iterator it;



		//for (auto vector : m_zVectors)
		//{
		//	vector.second->Sort();
		//	vector.second->QSort();
		//}


		//if (m_fps > 180)
		//	m_sortingDepth = 3;
		//else if (m_fps > 120)
		//	m_sortingDepth = 2;
		//else m_sortingDepth = 1;
		//
		//for (int32 i = 0; i < m_sortingDepth; i++)
		//{
		//	for (auto vector : m_zVectors)
		//	{
		//		vector.second->QSort();
		//	}
		//}

}

void RenderZMap::StaticSort()
{

	for (auto vector : m_zVectors)
	{
		vector.second->StaticSort();
		vector.second->StaticQSort();
	}
	

}

void _vectorcall RenderZMap::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct XMFLOAT4X4& viewMatrix,
	const struct XMFLOAT4X4& projectionMatrix,
	struct ShaderPackage &shader
) modern_except_state
{

	for (auto vector : m_zVectors)
	{
		vector.second->Render(deviceContext, viewMatrix, projectionMatrix, shader);
	}
}

void RenderZMap::Clear()
{
	for (auto vector : m_zVectors)
	{
		vector.second->Clear();
	}
}

void RenderZMap::Push(class Unit * const unit,const int64 z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(unit);
	}
	else
	{
		m_zVectors[z] = new EObjectVector();
		m_zVectors[z]->Push(unit);
		m_zStance[z] = true;
	}
}

void RenderZMap::Push(Doodads * doodads,const int64 z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(doodads);
	}
	else
	{
		m_zVectors[z] = new EObjectVector();
		m_zVectors[z]->Push(doodads);
		m_zStance[z] = true;
	}
}

void RenderZMap::Push(class AnimatedDoodads * animated,const int64 z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(animated);
	}
	else
	{
		m_zVectors[z] = new struct EObjectVector();
		m_zVectors[z]->Push(animated);
		m_zStance[z] = true;
	}
}

void RenderZMap::Push(class Tree * tree, const int64 z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(tree);
	}
	else
	{
		m_zVectors[z] = new struct EObjectVector();
		m_zVectors[z]->Push(tree);
		m_zStance[z] = true;
	}
}

void RenderZMap::Push(RegionPointObject* object, const int64 z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(object);
	}
	else
	{
		m_zVectors[z] = new struct EObjectVector();
		m_zVectors[z]->Push(object);
		m_zStance[z] = true;
	}
}

uint32_t RenderZMap::GetSize()
{
	uint32_t size = 0u;
	for (auto vector : m_zVectors)
	{
		//size += (uint32_t)vector.second->m_objectsXY[0].size();
	}
	return size;
}

__m128 RenderZMap::GetSizeX4()
{
	__m128 size{};
	for (auto vector : m_zVectors)
	{
	//	size.m128_uint32[0] += (uint32_t)vector.second->m_objectsX[0].size();
	//	size.m128_uint32[1] += (uint32_t)vector.second->m_objectsX[1].size();
	//	size.m128_uint32[2] += (uint32_t)vector.second->m_objectsX[2].size();
	//	size.m128_uint32[3] += (uint32_t)vector.second->m_objectsX[3].size();
	}
	return size;
}

std::vector<int64> RenderZMap::GetSizeVector()
{
	std::vector<int64> mv;
	for (auto vector : m_zVectors)
	{
		for (int32 i = 0; i < 16; ++i)
		{
		//	mv.push_back((uint32_t)vector.second->m_objectsX[i].size());
		}
	}
	return mv;
}

std::stack<Unit*> RenderZMap::GetUnitsInRange(class Unit * const object,const float range)
{
	if (object)
	{
		const int32 z = (int32)object->GetZ();
		return m_zVectors[z]->GetUnitsInRange(object, range);
	}
	class std::stack<class Unit*> m_elseStack;
	return m_elseStack;
}