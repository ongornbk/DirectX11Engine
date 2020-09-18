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
//#pragma omp for schedule(dynamic)//EASY CRASH
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
	__CleanUp(m_objectsXY[1]);
}

void _stdcall EObjectVector::Sort()
{
SortByXV(m_objectsXY);
SortByYV(m_objectsXY);

}

void _stdcall EObjectVector::QSort()
{
	QSortByXV(m_objectsXY);
	QSortByYV(m_objectsXY);

}

void _stdcall EObjectVector::StaticSort()
{
//	StaticSortByXV(m_objectsXY);
//	StaticSortByYV(m_objectsXY);
}

void _stdcall EObjectVector::StaticQSort()
{
//	StaticQSortByXV(m_objectsXY);
//	StaticQSortByYV(m_objectsXY);
}

//static uint32_t sizeg = 0u;



void _vectorcall EObjectVector::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct XMFLOAT4X4 & viewMatrix,
	const struct XMFLOAT4X4 & projectionMatrix,
	const struct ShaderPackage &shader
) noexcept
{
class modern_array<class modern_array<class EObject*>*> mvpp;


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

void _vectorcall EObjectVector::PreRender(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) noexcept
{
}

void EObjectVector::Clear()
{
	for (int32 cv = 0; cv < 32; cv++)
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

void EObjectVector::Push(
	class Unit * const unit
)
{
	m_objectsXY[1][0].push_back(unit);
}

void EObjectVector::Push(
	class Doodads * const doodads
)
{
	m_objectsXY[1][0].push_back(doodads);
}

void EObjectVector::Push(
	class AnimatedDoodads* const animated
)
{
	m_objectsXY[1][0].push_back(animated);
}

void EObjectVector::Push(
	class Tree * const tree
)
{
	m_objectsXY[1][0].push_back(tree);
}

void EObjectVector::Push(RegionPointObject* const tree)
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
	class std::stack<class Unit*> unitsLeft;
	class std::stack<class Unit*> unitsCenter;
	class std::stack<class Unit*> unitsRight;

	//std::stack<Unit*> unitsA[3];

	//ThreadPoolHandle pool; TO DO

	uint32 cVec = object->m_vector;


	switch (cVec)
	{
	case 0U:
	{

#pragma omp parallel
		{
#pragma omp single
			{
				for (auto& obj : m_objectsXY[1][cVec])
				{
					if (obj && obj != object && (obj->m_type == EObject::EObjectType::UNIT))
					{
						switch (CheckDistance(obj, object, range))
						{
						case 2:
							unitsCenter.push((Unit*)obj);
							break;
						}
					}
				}
			}
#pragma omp single
			{
				for (auto& obj : m_objectsXY[1][cVec + 1])
				{
					if (obj && obj != object && (obj->m_type == EObject::EObjectType::UNIT))
					{
						switch (CheckDistance(obj, object, range))
						{
						case 2:
							unitsRight.push((Unit*)obj);
							break;
						}
					}
				}
			}
	}
		break;
	}
	case 31U:
	{
#pragma omp parallel
		{
#pragma omp single
			{
				for (auto& obj : m_objectsXY[1][cVec - 1])
				{
					if (obj && obj != object && (obj->m_type == EObject::EObjectType::UNIT))
					{
						switch (CheckDistance(obj, object, range))
						{
						case 2:
							unitsLeft.push((Unit*)obj);
							break;
						}
					}
				}
			}
#pragma omp single
			{
				for (auto& obj : m_objectsXY[1][cVec])
				{
					if (obj && obj != object && (obj->m_type == EObject::EObjectType::UNIT))
					{
						switch (CheckDistance(obj, object, range))
						{
						case 2:
							unitsCenter.push((Unit*)obj);
							break;
						}
					}
				}
			}
		}
		break;
	}
	default:
	{
#pragma omp parallel
		{
#pragma omp single
			{
				for (auto& obj : m_objectsXY[1][cVec - 1])
				{
					if (obj && obj != object && (obj->m_type == EObject::EObjectType::UNIT))
					{
						switch (CheckDistance(obj, object, range))
						{
						case 2:
							unitsLeft.push((Unit*)obj);
							break;
						}
					}
				}
			}
#pragma omp single
			{
				for (auto& obj : m_objectsXY[1][cVec])
				{
					if (obj && obj != object && (obj->m_type == EObject::EObjectType::UNIT))
					{
						switch (CheckDistance(obj, object, range))
						{
						case 2:
							unitsCenter.push((Unit*)obj);
							break;
						}
					}
				}
			}
#pragma omp single
			{
				{
					for (auto& obj : m_objectsXY[1][cVec + 1])
						if (obj && obj != object && (obj->m_type == EObject::EObjectType::UNIT))
						{
							switch (CheckDistance(obj, object, range))
							{
							case 2:
								unitsRight.push((Unit*)obj);
								break;
							}
						}
				}
			}
		}
		break;
	}
	}
	
	while (!unitsLeft.empty()) {
		unitsCenter.push(unitsLeft.top());
		unitsLeft.pop();
	}

	while (!unitsRight.empty()) {
		unitsCenter.push(unitsRight.top());
		unitsRight.pop();
	}

	return unitsCenter;
}