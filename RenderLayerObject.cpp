#include "RenderLayerObject.h"
#include "modern/modern_guard.h"

RenderLayerObject::RenderLayerObject()
{
}

RenderLayerObject::~RenderLayerObject()
{
}

const RenderLayerType RenderLayerObject::GetType() const modern_except_state
{
	return RenderLayerType::ENUM_OBJECT_TYPE;
}

void RenderLayerObject::Update(const float dt)
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

void RenderLayerObject::CleanUp()
{
	__CleanUp(m_objects[1]);
}

void _stdcall RenderLayerObject::Sort()
{
		SortByXV(m_objects);
		SortByYV(m_objects);
}

void _stdcall RenderLayerObject::QSort()
{
//#pragma omp parallel
	//if (m_counter % 2)
	//{
		QSortByXV(m_objects);
		QSortByYV(m_objects);
	//}
	//else
	//{
	//	QSortByYV(m_objects);
	//	QSortByXV(m_objects);
	//}

	//m_counter++;

	PostSort();
//#pragma omp barrier
}

void _stdcall RenderLayerObject::StaticSort()
{
	//	StaticSortByXV(m_objectsXY);
//	StaticSortByYV(m_objectsXY);
}

void _stdcall RenderLayerObject::StaticQSort()
{
	//	StaticQSortByXV(m_objectsXY);
//	StaticQSortByYV(m_objectsXY);
}

void _vectorcall RenderLayerObject::Render(
	struct ID3D11DeviceContext* const deviceContext,
	const DirectX::XMFLOAT4X4& viewMatrix,
	const DirectX::XMFLOAT4X4& projectionMatrix,
	const struct ShaderPackage& shader
) modern_except_state
{
	class modern_array<class modern_array<class EObject*>*> mvpp;


	for (int32 i = 0; i < MAP_DIVISION; i++)
	{
		if (!yta[i])
			mvpp.push_back(&m_objects[1][i]);
	}

	std::reverse(mvpp.begin(), mvpp.end());

	uint32 group = MAP_DIVISION -1;
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

void _vectorcall RenderLayerObject::PreRender(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) modern_except_state
{

}

void RenderLayerObject::Clear()
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

void RenderLayerObject::Push(Unit* const unit)
{
	m_objects[1][0].push_back(unit);
}

void RenderLayerObject::Push(Doodads* const doodads)
{
	m_objects[1][0].push_back(doodads);
}

void RenderLayerObject::Push(AnimatedDoodads* const animated)
{
	m_objects[1][0].push_back(animated);
}

void RenderLayerObject::Push(Tree* const tree)
{
	m_objects[1][0].push_back(tree);
}

void RenderLayerObject::Push(RegionPointObject* const tree)
{
	m_objects[1][0].push_back(tree);
}

void RenderLayerObject::Push(EObject* const agent)
{
	m_objects[1][0].push_back(agent);
}

void RenderLayerObject::Push(Interface* const inter)
{
}

int64_t _fastcall CheckDistance(
	class EObject* const A,
	class EObject* const B,
	const float range
) modern_except_state
{

	const float distanceX = A->m_boundingSphere.Center.x - B->m_boundingSphere.Center.x;
	const float distanceY = A->m_boundingSphere.Center.y - B->m_boundingSphere.Center.y;
	const float distance = DirectX::XMVector2Length({ distanceX,distanceY }).m128_f32[0];
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

void _stdcall PushUnitsInRange(vector<EObject*>& vec, std::stack<Unit*>& sa, EObject* agent, const float range) modern_except_state
{
	
	for (auto&& unit : vec)
	{
		if (unit && unit != agent && (unit->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
		{
			switch (CheckDistance(unit, agent, range))
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


std::stack<Unit*> _vectorcall RenderLayerObject::GetUnitsInRange(Unit* agent, float range) modern_except_state
{
	
	class std::stack<class Unit*> unitsLeft;
	class std::stack<class Unit*> unitsCenter;
	class std::stack<class Unit*> unitsRight;

	//std::stack<Unit*> unitsA[3];

	//ThreadPoolHandle pool; TO DO

	uint32 cVec = agent->m_vector;
	uint32 VIndex = agent->m_index;

	switch (cVec)
	{
	case 0U:
	{

//#pragma omp parallel num_threads(2)
		{
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsCenter.push((Unit*)obj);
							break;
						}
					}
				}
			}
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec + 1])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
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
//#pragma omp parallel num_threads(2)
		{
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec - 1])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsLeft.push((Unit*)obj);
							break;
						}
					}
				}
			}
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
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
//#pragma omp parallel num_threads(3)
		{
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec - 1])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsLeft.push((Unit*)obj);
							break;
						}
					}
				}
			}
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsCenter.push((Unit*)obj);
							break;
						}
					}
				}
			}
//#pragma omp single
			{
				{
					for (auto& obj : m_objects[1][cVec + 1])
						if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
						{
							switch (CheckDistance(obj, agent, range))
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

std::stack<class Unit*> _vectorcall RenderLayerObject::GetUnitsInRange(Agent* agent, float range) modern_except_state
{
	class std::stack<class Unit*> unitsLeft;
	class std::stack<class Unit*> unitsCenter;
	class std::stack<class Unit*> unitsRight;

	//std::stack<Unit*> unitsA[3];

	//ThreadPoolHandle pool; TO DO

	uint32 cVec = agent->m_vector;
	uint32 VIndex = agent->m_index;

	switch (cVec)
	{
	case 0U:
	{

		//#pragma omp parallel num_threads(2)
		{
			//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsCenter.push((Unit*)obj);
							break;
						}
					}
				}
			}
			//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec + 1])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
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
		//#pragma omp parallel num_threads(2)
		{
			//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec - 1])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsLeft.push((Unit*)obj);
							break;
						}
					}
				}
			}
			//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
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
		//#pragma omp parallel num_threads(3)
		{
			//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec - 1])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsLeft.push((Unit*)obj);
							break;
						}
					}
				}
			}
			//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
					{
						switch (CheckDistance(obj, agent, range))
						{
						case 2:
							unitsCenter.push((Unit*)obj);
							break;
						}
					}
				}
			}
			//#pragma omp single
			{
				{
					for (auto& obj : m_objects[1][cVec + 1])
						if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT))
						{
							switch (CheckDistance(obj, agent, range))
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



















































	//return std::stack<class Unit*>();
}

std::stack<class Tree*> _vectorcall RenderLayerObject::GetTreesBelow(class EObject* const agent, float range) modern_except_state
{

	class std::stack<class Tree*> m_trees;

	uint32 cVec = agent->m_vector;
	uint32 cIndex = agent->m_index;

	modern_array_iterator<EObject*> it = 
		(cIndex > 0 && cIndex < m_objects[1][cVec].size()) ? 
		modern_array_iterator<EObject*>(m_objects[1][cVec].begin() + cIndex, m_objects[1][cVec].end()) : 
		modern_array_iterator<EObject*>(m_objects[1][cVec].begin(), m_objects[1][cVec].end());



		for (auto& obj : it)
		{
			if (obj && obj != agent && (obj->m_type == EObject::EObjectType::OBJECT_TYPE_TREE))
			{
				switch (CheckDistance(obj, agent, range))
				{
				case 0:
				{
					goto ENDLOOP;
					//break;
				}
				case 2:
					m_trees.push((Tree*)obj);
					break;
				}
				
			}
		}

		ENDLOOP:

	return m_trees;
}
