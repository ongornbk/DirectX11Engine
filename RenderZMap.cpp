#include "RenderZMap.h"

RenderZMap::RenderZMap()
{
	ZeroMemory(&m_zStance, sizeof(bool) * 256);
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

void RenderZMap::Update(float dt)
{
	for (auto vector : m_zVectors)
	{
		vector.second->Update(dt);
	}
}

void RenderZMap::Sort()
{
	for (auto vector : m_zVectors)
	{
		vector.second->Sort();
	}
}

void _vectorcall RenderZMap::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader * shader) noexcept
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

void RenderZMap::Push(Unit * unit, int8_t z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(unit);
	}
	else
	{
		m_zVectors[z] = new RenderContainerVector();
		m_zVectors[z]->Push(unit);
		m_zStance[z] = true;
	}
}

void RenderZMap::Push(Doodads * doodads, int8_t z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(doodads);
	}
	else
	{
		m_zVectors[z] = new RenderContainerVector();
		m_zVectors[z]->Push(doodads);
		m_zStance[z] = true;
	}
}

void RenderZMap::Push(AnimatedDoodads * animated, int8_t z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(animated);
	}
	else
	{
		m_zVectors[z] = new RenderContainerVector();
		m_zVectors[z]->Push(animated);
		m_zStance[z] = true;
	}
}

void RenderZMap::Push(Tree * tree, int8_t z)
{
	if (m_zStance[z])
	{
		m_zVectors[z]->Push(tree);
	}
	else
	{
		m_zVectors[z] = new RenderContainerVector();
		m_zVectors[z]->Push(tree);
		m_zStance[z] = true;
	}
}

uint32_t RenderZMap::GetSize()
{
	uint32_t size = 0u;
	for (auto vector : m_zVectors)
	{
		size += (uint32_t)vector.second->m_objectsY[0].size();
	}
	return size;
}

__m128 RenderZMap::GetSizeX4()
{
	__m128 size{};
	for (auto vector : m_zVectors)
	{
		size.m128_u32[0] += (uint32_t)vector.second->m_objectsX[0].size();
		size.m128_u32[1] += (uint32_t)vector.second->m_objectsX[1].size();
		size.m128_u32[2] += (uint32_t)vector.second->m_objectsX[2].size();
		size.m128_u32[3] += (uint32_t)vector.second->m_objectsX[3].size();
	}
	return size;
}

std::vector<uint32_t> RenderZMap::GetSizeVector()
{
	std::vector<uint32_t> mv;
	for (auto vector : m_zVectors)
	{
		for (uint32_t i = 0u; i < 16u; i++)
		{
			mv.push_back((uint32_t)vector.second->m_objectsX[i].size());
		}
	}
	return mv;
}

std::stack<Unit*> _vectorcall RenderZMap::GetUnitsInRange(Unit * object, float range)
{
	if (object)
	{
		int8_t z = (int8_t)object->GetZ();
		return m_zVectors[z]->GetUnitsInRange(object, range);
	}
	std::stack<Unit*> m_elseStack;
	return m_elseStack;
}