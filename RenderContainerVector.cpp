#include "RenderContainerVector.h"
#include "Sorting.h"
#include "Defines.h"
#include "Vector.h"
#include "ThreadPool.h"
#include "Engine.h"
#include <thread>

typedef int32_t Boolean;

EObjectVector::EObjectVector()
{
}



void EObjectVector::Update(
	const float dt
)
{
	for (int32 i = 0; i < 32; ++i)
	{
		if(!xta[i])
		for (auto & obj : m_objectsXY[1][i])
		{
			if (obj)
				obj->Update(dt);
		}
	}
}

void EObjectVector::CleanUp()
{
	__CleanUp(m_objectsXY);
}

void EObjectVector::Sort()
{
	SortByXV(m_objectsXY);
	SortByYV(m_objectsXY);
}

//static uint32_t sizeg = 0u;



void _vectorcall EObjectVector::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct XMFLOAT4X4 & viewMatrix,
	const struct XMFLOAT4X4 & projectionMatrix,
	const struct ShaderPackage &shader
) noexcept
{
class Vector<class Vector<class EObject*>*> mvpp;
for (int32 i = 0; i < 32; i++)
	{
	if(!yta[i])
mvpp.push_back(&m_objectsXY[1][i]);
	}

std::reverse(mvpp.begin(), mvpp.end());

uint32 group = 31u;
for (auto& vec : mvpp)
{
	GRAPHICS EnableAlphaBlending(true);

	shader.BeginShadow();


	for (auto& obj : *vec)
	{
		obj->PreRender(deviceContext, viewMatrix, projectionMatrix, shader);
	}

	GRAPHICS EnableAlphaBlending(false);


	//shader.End();
	shader.BeginStandard();

	uint32 index = 0u;
	for (auto& obj : *vec)
	{
		obj->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		obj->m_index = index;
		obj->m_vector = group;
		index++;
	}
	group--;

	//shader.End();
}

}

void EObjectVector::Clear()
{
	for (uint32 cv = 0u; cv < 32u; cv++)
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

void EObjectVector::Push(Unit * unit)
{
	m_objectsXY[1][0].push_back(unit);
}

void EObjectVector::Push(Doodads * doodads)
{
	m_objectsXY[1][0].push_back(doodads);
}

void EObjectVector::Push(AnimatedDoodads* animated)
{
	m_objectsXY[1][0].push_back(animated);
}

void EObjectVector::Push(Tree * tree)
{
	m_objectsXY[1][0].push_back(tree);
}

Boolean _fastcall CheckDistance(
	class EObject* const A,
	class EObject* const B,
	const float range
) noexcept
{

	const float distanceX = A->m_boundingSphere.Center.x - B->m_boundingSphere.Center.x;
	const float distanceY = A->m_boundingSphere.Center.y - B->m_boundingSphere.Center.y;
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

void _stdcall PushUnitsInRange(vector<EObject*>& vec, std::stack<Unit*>& sa, EObject* object,const float range) noexcept
{
	for (auto&& unit : vec)
	{
		if (unit&&unit != object && (unit->m_type == EObject::EObjectType::UNIT))
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


std::stack<Unit*> _vectorcall EObjectVector::GetUnitsInRange(Unit* object, float range) noexcept
{
	std::stack<Unit*> units;

	//std::stack<Unit*> unitsA[3];

	//ThreadPoolHandle pool; TO DO

	const uint32 cVec = object->m_vector;

	switch (cVec)
	{
	case 0U:
	{


		for (auto &obj : m_objectsXY[1][cVec])
		{
			if (obj&&obj != object && (obj->m_type == EObject::EObjectType::UNIT))
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
			if (obj&&obj != object && (obj->m_type == EObject::EObjectType::UNIT))
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
			if (obj&&obj != object && (obj->m_type == EObject::EObjectType::UNIT))
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
			if (obj&&obj != object && (obj->m_type == EObject::EObjectType::UNIT))
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
			if (obj&&obj != object && (obj->m_type == EObject::EObjectType::UNIT))
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
			if (obj&&obj != object && (obj->m_type == EObject::EObjectType::UNIT))
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
			if (obj&&obj != object && (obj->m_type == EObject::EObjectType::UNIT))
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