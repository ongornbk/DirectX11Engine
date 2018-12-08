#include "RenderContainerVector.h"
#include "Sorting.h"
#include "Defines.h"
#include "Vector.h"
#include "ThreadPool.h"
#include <thread>

typedef int32_t Boolean;

RenderContainerVector::RenderContainerVector()
{
}



void RenderContainerVector::Update(float dt)
{
	for (u32 i = 0u; i < 32u; i++)
	{
		if(!xta[i])
		for (auto & obj : m_objectsXY[1][i])
		{
			if (obj)
				obj->Update(dt);
		}
	}
}

void RenderContainerVector::Sort()
{
	SortByXV(m_objectsXY);
	SortByYV(m_objectsXY);
}

//static uint32_t sizeg = 0u;



void _vectorcall RenderContainerVector::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) noexcept
{
Vector<Vector<RenderContainer*>*> mvpp;
for (uint16_t i = 0u; i < 32u; i++)
	{
	if(!yta[i])
mvpp.push_back(&m_objectsXY[1][i]);
	}

std::reverse(mvpp.begin(), mvpp.end());

u32 group = 31u;
for (auto& vec : mvpp)
{
	u32 index = 0u;
	for (auto& obj : *vec)
	{
		obj->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		obj->m_index = index;
		obj->m_vector = group;
		index++;
	}
	group--;
}

}

void RenderContainerVector::Clear()
{
	for (u32 cv = 0u; cv < 32u; cv++)
	{
		for (auto &&object : m_objectsXY[0][cv])
		{
			if (object)
			{
				object->Release();
				object = nullptr;
			}
		}
		m_objectsXY[0][cv].clear();
		m_objectsXY[1][cv].clear();
	}

}

void RenderContainerVector::Push(Unit * unit)
{
	m_objectsXY[1][0].push_back(unit);
}

void RenderContainerVector::Push(Doodads * doodads)
{
	m_objectsXY[1][0].push_back(doodads);
}

void RenderContainerVector::Push(AnimatedDoodads* animated)
{
	m_objectsXY[1][0].push_back(animated);
}

void RenderContainerVector::Push(Tree * tree)
{
	m_objectsXY[1][0].push_back(tree);
}

Boolean _stdcall CheckDistance(RenderContainer* A, RenderContainer* B, float range) noexcept
{

	const float distanceX = A->Center.x - B->Center.x;
	const float distanceY = A->Center.y - B->Center.y;
	const float distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
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

void _stdcall PushUnitsInRange(vector<RenderContainer*>& vec, std::stack<Unit*>& sa, RenderContainer* object, float range) noexcept
{
	for (auto&& unit : vec)
	{
		if (unit&&unit != object && (unit->m_type == RenderContainer::RenderContainerType::UNIT))
		{
			switch (CheckDistance(unit, object, range))
			{
			case 2:
				sa.push((Unit*)unit);
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

	//std::stack<Unit*> unitsA[3];

	//ThreadPoolHandle pool; TO DO

	const u32 cVec = object->m_vector;

	switch (cVec)
	{
	case 0U:
	{


		for (auto &obj : m_objectsXY[1][cVec])
		{
			if (obj&&obj != object && (obj->m_type == RenderContainer::RenderContainerType::UNIT))
			{
				switch (CheckDistance(obj, object, range))
				{
				case 2:
					units.push((Unit*)obj);
					break;
				}
			}
		}
		for (auto &obj : m_objectsXY[1][cVec+1])
		{
			if (obj&&obj != object && (obj->m_type == RenderContainer::RenderContainerType::UNIT))
			{
				switch (CheckDistance(obj, object, range))
				{
				case 2:
					units.push((Unit*)obj);
					break;
				}
			}
		}
		break;
	}
	case 31U:
	{
		for (auto &obj : m_objectsXY[1][cVec - 1])
		{
			if (obj&&obj != object && (obj->m_type == RenderContainer::RenderContainerType::UNIT))
			{
				switch (CheckDistance(obj, object, range))
				{
				case 2:
					units.push((Unit*)obj);
					break;
				}
			}
		}
		for (auto &obj : m_objectsXY[1][cVec])
		{
			if (obj&&obj != object && (obj->m_type == RenderContainer::RenderContainerType::UNIT))
			{
				switch (CheckDistance(obj, object, range))
				{
				case 2:
					units.push((Unit*)obj);
					break;
				}
			}
		}
		break;
	}
	default:
	{
		for (auto &obj : m_objectsXY[1][cVec - 1])
		{
			if (obj&&obj != object && (obj->m_type == RenderContainer::RenderContainerType::UNIT))
			{
				switch (CheckDistance(obj, object, range))
				{
				case 2:
					units.push((Unit*)obj);
					break;
				}
			}
		}
		for (auto &obj : m_objectsXY[1][cVec])
		{
			if (obj&&obj != object && (obj->m_type == RenderContainer::RenderContainerType::UNIT))
			{
				switch (CheckDistance(obj, object, range))
				{
				case 2:
					units.push((Unit*)obj);
					break;
				}
			}
		}
		{
			for (auto &obj : m_objectsXY[1][cVec + 1])
			if (obj&&obj != object && (obj->m_type == RenderContainer::RenderContainerType::UNIT))
			{
				switch (CheckDistance(obj, object, range))
				{
				case 2:
					units.push((Unit*)obj);
					break;
				}
			}
		}
		break;
	}
	}
	

	return units;
}