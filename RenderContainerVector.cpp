#include "RenderContainerVector.h"
#include "Sorting.h"
#include <thread>

typedef int32_t Boolean;

RenderContainerVector::RenderContainerVector()
{

}

void _vectorcall UpdatePart(std::vector<RenderContainer*> vec, float dt) noexcept
{
	RenderContainer** m_array = vec.data();
	for (uint32_t i = 0u; i < vec.size(); ++i)
	{
		m_array[i]->Update(dt);
	}
}

void _cdecl UpdatePartP(std::vector<RenderContainer*> vec, float dt)
{
	UpdatePart(vec, dt);
}

void RenderContainerVector::Update(float dt)
{

	UpdatePart(m_objectsY[0], dt);
	UpdatePart(m_objectsY[1], dt);
	UpdatePart(m_objectsY[2], dt);
	UpdatePart(m_objectsY[3], dt);

	//std::thread t0(UpdatePartP, m_objectsY[0], dt);
	//std::thread t1(UpdatePartP, m_objectsY[1], dt);
	//std::thread t2(UpdatePartP, m_objectsY[2], dt);
	//std::thread t3(UpdatePartP, m_objectsY[3], dt);
	//
	//t0.join();
	//t1.join();
	//t2.join();
	//t3.join();
}

void RenderContainerVector::Sort()
{
	SortByX(m_objectsX, m_objectsY);
	SortByY(m_objectsY, m_objectsX);
}

static uint32_t sizeg = 0u;

void _vectorcall RenderContainerVector::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader * shader) noexcept
{
	RenderContainer** objects0 = m_objectsY[0].data();
	RenderContainer** objects1 = m_objectsY[1].data();
	RenderContainer** objects2 = m_objectsY[2].data();
	RenderContainer** objects3 = m_objectsY[3].data();

	for (uint32_t i = 0; i < (uint32_t)m_objectsY[0].size(); i++)
	{
		objects0[i]->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		objects0[i]->m_index = i;
	}
	for (uint32_t i = 0; i < (uint32_t)m_objectsY[1].size(); i++)
	{
		objects1[i]->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		objects1[i]->m_index = i;
	}
	for (uint32_t i = 0; i < (uint32_t)m_objectsY[2].size(); i++)
	{
		objects2[i]->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		objects2[i]->m_index = i;
	}
	for (uint32_t i = 0; i < (uint32_t)m_objectsY[3].size(); i++)
	{
		objects3[i]->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		objects3[i]->m_index = i;
	}
}

void RenderContainerVector::Clear()
{
	for (uint32_t cv = 0u; cv < 4u; cv++)
	{
		for (auto &&object : m_objectsY[cv])
		{
			if (object)
			{
				object->Release();
				object = nullptr;
			}
		}
		m_objectsX[cv].clear();
		m_objectsY[cv].clear();
	}

}

void RenderContainerVector::Push(Unit * unit)
{
	m_objectsY[0].push_back(unit);
}

void RenderContainerVector::Push(Doodads * doodads)
{
	m_objectsY[0].push_back(doodads);
}

void RenderContainerVector::Push(AnimatedDoodads* animated)
{
	m_objectsY[0].push_back(animated);
}

void RenderContainerVector::Push(Tree * tree)
{
	m_objectsY[0].push_back(tree);
}

Boolean _stdcall CheckDistance(RenderContainer* a, RenderContainer* b, float range) noexcept
{

	BoundingSphere* bsa = a->GetBoundingSphere();
	BoundingSphere* bsb = b->GetBoundingSphere();

	float distanceX = bsa->Center.x - bsb->Center.x;
	float distanceY = bsa->Center.y - bsb->Center.y;
	float distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
	if (distance < range)
	{
		return 2;
	}
	else
	{
		if (distanceY < range)
			return 1;
		else return 0;
	}
}

void _stdcall PushUnitsInRange(std::vector<RenderContainer*>* vec, atomic<std::stack<Unit*>*>* sa, RenderContainer* object, float range) noexcept
{
	for (auto unit : *vec)
	{
		if (unit&&unit != object && (unit->m_type == RenderContainer::RenderContainerType::UNIT))
		{
			switch (CheckDistance(unit, object, range))
			{
			case 2:
				sa->load()->push((Unit*)unit);
				break;
			case 1:
				break;
			case 0:
				goto ENDLOOP;
			}
		}
	}
ENDLOOP:
	return;
}

std::stack<Unit*> _vectorcall RenderContainerVector::GetUnitsInRange(Unit* object, float range) noexcept
{
	std::stack<Unit*> units;
	//atomic<std::stack<Unit*>*> sa = &units;
	//std::vector<RenderContainer*>* upv = &g_units.m_zVectors[(int8_t)object->GetZ()]->m_objectsY;
	//size_t index = (size_t)object->m_index;
	//
	//std::vector<RenderContainer*> fv(upv->begin(), upv->begin() + index);
	//std::reverse(fv.begin(), fv.end());
	//std::vector<RenderContainer*> sv(upv->begin() + index, upv->end());
	//m_async = 2;
	//std::async(std::launch::async, PushUnitsInRange, &fv, &sa, object, range);
	//std::async(std::launch::async, PushUnitsInRange, &sv, &sa, object, range);
	//while (m_async)
	//{
	//	DoNothing();
	//}
	return units;
}