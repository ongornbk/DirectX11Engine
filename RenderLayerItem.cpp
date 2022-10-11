#include "RenderLayerItem.h"

RenderLayerItem::RenderLayerItem()
{
}

RenderLayerItem::~RenderLayerItem()
{
}

const RenderLayerType RenderLayerItem::GetType() const modern_except_state
{
	return RenderLayerType::ENUM_ITEM_TYPE;
}

void RenderLayerItem::Update(const float dt)
{
	m_size = 0ull;
	for (int32_t i = 0; i < MAP_DIVISION; ++i)
	{
		if (!xta[i])
			for (auto& obj : m_objects[1][i])
			{
				if (obj)
					obj->Update(dt);
			}
	}
//#pragma omp barrier
}

void RenderLayerItem::CleanUp()
{
	__CleanUp(m_objects[1]);
}

void _stdcall RenderLayerItem::Sort()
{
}

void _stdcall RenderLayerItem::QSort()
{
}

void _stdcall RenderLayerItem::StaticSort()
{
}

void _stdcall RenderLayerItem::StaticQSort()
{
}

void _vectorcall RenderLayerItem::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) modern_except_state
{
	class modern_array<class modern_array<class GameObject*>*> mvpp;


	for (int32 i = 0; i < MAP_DIVISION; i++)
	{
		if (!yta[i])
			mvpp.push_back(&m_objects[1][i]);
	}

	std::reverse(mvpp.begin(), mvpp.end());

	uint32 group = MAP_DIVISION -1u;
	for (auto& vec : mvpp)
	{
		GRAPHICS EnableAlphaBlending(true);

		//shader.BeginShadow();


		//for (auto& obj : *vec)
		//{
		//	obj->PreRender(deviceContext, viewMatrix, projectionMatrix, shader);
		//}

		//GRAPHICS EnableAlphaBlending(false);


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
	}
}

void _vectorcall RenderLayerItem::PreRender(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader) modern_except_state
{
}

void RenderLayerItem::Clear()
{
	for (int32 cv = 0; cv < MAP_DIVISION; cv++)
	{
		for (auto&& object : m_objects[0][cv])
		{
			if (object)
			{
				object->Release();
				object = nullptr;
			}
		}
		m_objects[0][cv].clear();
		m_objects[1][cv].clear();
	}
}

void RenderLayerItem::Push(Unit* const unit)
{
	m_objects[1][0].push_back(unit);
}

void RenderLayerItem::Push(Doodads* const doodads)
{
	m_objects[1][0].push_back(doodads);
}

void RenderLayerItem::Push(AnimatedDoodads* const animated)
{
	m_objects[1][0].push_back(animated);
}

void RenderLayerItem::Push(Tree* const tree)
{
	m_objects[1][0].push_back(tree);
}

void RenderLayerItem::Push(RegionPointObject* const tree)
{
	m_objects[1][0].push_back(tree);
}

void RenderLayerItem::Push(GameObject* const object)
{
	m_objects[1][0].push_back(object);
}

void RenderLayerItem::Push(Interface* const inter)
{
}

static int64_t _fastcall CheckDistance(
	class GameObject* const A,
	class GameObject* const B,
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

static void _stdcall PushUnitsInRange(vector<GameObject*>& vec, std::stack<Unit*>& sa, GameObject* object, const float range) modern_except_state
{

	for (auto&& unit : vec)
	{
		if (unit && unit != object && (unit->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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


std::stack<Unit*> _vectorcall RenderLayerItem::GetUnitsInRange(Unit* object, float range) modern_except_state
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

//#pragma omp parallel num_threads(2)
		{
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != object && (obj->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec + 1])
				{
					if (obj && obj != object && (obj->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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
//#pragma omp parallel num_threads(2)
		{
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec - 1])
				{
					if (obj && obj != object && (obj->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != object && (obj->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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
//#pragma omp parallel num_threads(3)
		{
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec - 1])
				{
					if (obj && obj != object && (obj->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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
//#pragma omp single
			{
				for (auto& obj : m_objects[1][cVec])
				{
					if (obj && obj != object && (obj->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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
//#pragma omp single
			{
				{
					for (auto& obj : m_objects[1][cVec + 1])
						if (obj && obj != object && (obj->m_type == GameObject::EObjectType::OBJECT_TYPE_UNIT))
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

std::stack<class Unit*> _vectorcall RenderLayerItem::GetUnitsInRange(Agent* agent, float range) modern_except_state
{
	return std::stack<class Unit*>();
}

std::stack<class Tree*> _vectorcall RenderLayerItem::GetTreesBelow(class GameObject* const object, float range) modern_except_state
{
	return std::stack<class Tree*>();
}
