#include "RendererManager.h"
#include "IPP.h"
#include "SettingsC.h"
#include "Defines.h"
#include <future>
#include <mutex>
#include <stack>


#pragma region
class Unit;
#define UnitPtr Unit*;
#pragma endregion

namespace
{
	RendererManager*              m_instance;
	Engine*                       m_engine;
	static XMVECTOR               m_cameraPosition;
	static float                  m_ranges[2];
	static atomic<int>            m_coord[2];
	atomic<uint8_t>               m_async;
	static RenderZMap             g_units;
	//std::mutex                    m_validateMutex;
}

RendererManager::RendererManager(Engine* engine,Shader* units,Shader* ui)
{
	this->m_renderingStyle = RendererManager::RenderingStyle::REVERSE;
	this->m_engine = engine;
	this->m_unitsShader = units;
	this->m_shader = ui;




	m_instance = this;
	
	Tile::SetGlobals(Engine::GetEngine()->GetGraphics()->GetDevice(), GETSHADER "tile.fx" CLOSE,this);
	m_map = new TileMap(1.0f,1.0f,0.2f,true);
	m_map->Initialize();
	TileMap::SetCurrentTileMap(m_map);
	Tile::SetDeviceContext(Engine::GetEngine()->GetGraphics()->GetDeviceContext());
	m_ui = new UserInterface();
	m_ranges[0] = ((float)*(SETTINGS RESOLUTION_X) / 2.0f)+300.0f;
	m_ranges[1] = ((float)*(SETTINGS RESOLUTION_Y) / 2.0f) + 300.0f;

}


RendererManager::~RendererManager()
{
	g_units.Clear();
	if (m_ui)
	{
		delete m_ui;
		m_ui = NULL;
	}
	if (m_map)
	{
		delete m_map;
		m_map = nullptr;
	}
}



void RendererManager::PushUnit(Unit * unit,int8_t z)
{
	g_units.Push(unit,z);
}

void RendererManager::PushDoodads(Doodads * doodads, int8_t z)
{
	g_units.Push(doodads,z);
}

void RendererManager::PushAnimatedDoodads(AnimatedDoodads * doodads, int8_t z)
{
	g_units.Push(doodads,z);
}

void RendererManager::PushTree(Tree * doodads, int8_t z)
{
	g_units.Push(doodads,z);
}

extern "C"
{

	//bool Intersects(RenderContainer* a, RenderContainer* b)
	//{
	//	return a->GetBoundingSphere()->Intersects(*b->GetBoundingSphere());
	//}

	struct __SortByY {
		bool operator()(RenderContainer* a, RenderContainer* b) const noexcept {

			BoundingSphere* bsa = a->GetBoundingSphere();
			BoundingSphere* bsb = b->GetBoundingSphere();

			bool af2 = a->Flag(2u);
			bool bf2 = b->Flag(2u);

			float radius[3];
			float ax, ay, bx, by;

			radius[0] = bsa->Radius;
			radius[1] = bsb->Radius;
			ax = bsa->Center.x;
			ay = bsa->Center.y;

			bx = bsb->Center.x;
			by = bsb->Center.y;

			//if (radius[0] == 0.0f||radius[1] == 0.0f) goto RETURN;
			radius[2] = radius[0] + radius[1];
			float distance = 0.0f;
			float distanceX = 0.0f, distanceY = 0.0f;
			float collision = 0.0f;



			

				



			distanceX = ax - bx;
			distanceY = ay - by;
			distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
			if (distance < radius[2])
			{
				collision = distance - radius[2];
				if (af2)
				{
					if (bf2)
					{
						collision /= 2.0f;
						if (ax < bx)
						{
							bsa->Center.x += collision;
							bsb->Center.x -= collision;
						}
						else
						{
							bsa->Center.x -= collision;
							bsa->Center.x += collision;

						}
						//a->UpdatePosition();
						//b->UpdatePosition();
					}
					else
					{
						if (ax < bx) bsa->Center.x += collision;
						else         bsa->Center.x -= collision;

						//a->UpdatePosition();
					}
				}
				else
				{
					if (bf2)
					{
						if (ax < bx) bsb->Center.x -= collision;
						else         bsb->Center.x += collision;


						//b->UpdatePosition();
					}

				}

			}
		//RETURN:

			return ay > by;
		}
	};

	struct  __SortByX {
		bool operator()(RenderContainer *a, RenderContainer *b) const noexcept {

			BoundingSphere* bsa = a->GetBoundingSphere();
			BoundingSphere* bsb = b->GetBoundingSphere();

			bool af2 = a->Flag(2u);
			bool bf2 = b->Flag(2u);

			float radius[3];
			float ax, ay, bx, by;

			radius[0] = bsa->Radius;
			radius[1] = bsb->Radius;

			ax = bsa->Center.x;
			ay = bsa->Center.y;

			bx = bsb->Center.x;
			by = bsb->Center.y;

			//if (radius[0] == 0.0f|| radius[1] == 0.0f) goto RETURN;
			radius[2] = radius[0] + radius[1];
			float distance = 0.0f;
			float distanceX = 0.0f, distanceY = 0.0f;
			float collision = 0.0f;

			distanceX = ax - bx;
			distanceY = ay - by;
			distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
			if (distance < radius[2])
			{
				collision = distance - radius[2];
				if (af2)
				{
					if (bf2)
					{
						collision /= 2.0f;
						if (ay < by)
						{
							bsa->Center.y += collision;
							bsb->Center.y -= collision;
						}
						else
						{
							bsa->Center.y -= collision;
							bsb->Center.y += collision;
						}
					}
					else
					{
						if (ay < by) bsa->Center.y += collision;
						else         bsa->Center.y -= collision;

					}
				}
				else
				{
					if (bf2)
					{
						if (ay < by) bsb->Center.y -= collision;
						else         bsb->Center.y += collision;
					}

				}

			}
		//RETURN:

			return ax > bx;
		}
	};

	bool _cdecl CollisionSortingXY  (RenderContainer* a,RenderContainer* b) noexcept
	{

		BoundingSphere* bsa = a->GetBoundingSphere();
		BoundingSphere* bsb = b->GetBoundingSphere();

		bool af2 = a->Flag(2u);
		bool bf2 = b->Flag(2u);

		float radius[3];
		float ax, ay, bx, by;

		radius[0] = bsa->Radius;
		radius[1] = bsb->Radius;
		ax = bsa->Center.x;
		ay = bsa->Center.y;

		bx = bsb->Center.x;
		by = bsb->Center.y;

		if (radius[0] == 0.0f || radius[1] == 0.0f) goto RETURN;
		radius[2] = radius[0] + radius[1];
		float distance = 0.0f;
		float distanceX = 0.0f, distanceY = 0.0f;
		float collision = 0.0f;









		distanceX = ax - bx;
		distanceY = ay - by;

		//float xratio = distanceX / distanceY;
		//float yratio = distanceY / distanceX;

		distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
		if (distance < radius[2])
		{
			collision = distance - radius[2];
			if (af2)
			{
				if (bf2)
				{
					collision /= 2.0f;
					if (ax < bx)
					{
						bsa->Center.x += collision;// *xratio;
						bsb->Center.x -= collision;// *xratio;
					}
					else
					{
						bsa->Center.x -= collision;// *xratio;
						bsa->Center.x += collision;// *xratio;
					}
					//if (ay < by)
					//{
					//	a->m_yOffset += collision;// *yratio;
					//	a->m_yOffset -= collision;// *yratio;
					//}
					//else
					//{
					//	a->m_yOffset -= collision;// *yratio;
					//	a->m_yOffset += collision;// *yratio;
					//}
					//a->UpdatePosition();
					//b->UpdatePosition();
				}
				else
				{
					if (ax < bx) bsa->Center.x += collision;// *xratio;
					else         bsa->Center.x -= collision;// *xratio;
					//if (ay < by) a->m_yOffset += collision;// *yratio;
				//	else         a->m_yOffset -= collision;;// *yratio;

				}
			}

			else
			{
				if (bf2)
				{
					if (ax < bx) bsb->Center.x -= collision;// *xratio;
					else         bsb->Center.x += collision;// *xratio;
				//	if (ay < by) a->m_yOffset -= collision;
				//	else         a->m_yOffset += collision;

					//b->UpdatePosition();
				}

			}
		}
		
	RETURN:

		return ay > by;
	}

	void _cdecl sortPy(std::vector<RenderContainer*>::iterator begin, std::vector<RenderContainer*>::iterator end)
	{
		std::sort(begin, end, __SortByY());
	}

	void SortByY(std::vector<RenderContainer*> &vec) noexcept
	{
		constexpr float MAP_XEND = (TILE_MAP_SIZE / 2.0f) * 160.0f;
		constexpr float MAP_XBEG = (TILE_MAP_SIZE / 2.0f) * -160.0f;
		constexpr float MAP_XENDd2 = (TILE_MAP_SIZE / 2.0f) * 80.0f;
		constexpr float MAP_XBEGd2 = (TILE_MAP_SIZE / 2.0f) * -80.0f;
		//constexpr float MAP_YEND = (TILE_MAP_SIZE / 2.0f) * 80.0f;
		//constexpr float MAP_YBEG = (TILE_MAP_SIZE / 2.0f) * -80.0f;

		std::vector<RenderContainer*> vec0;
		std::vector<RenderContainer*> vec1;
		std::vector<RenderContainer*> vec2;
		std::vector<RenderContainer*> vec3;
		for (auto && RC : vec)
		{
			if (RC->GetBoundingSphere()->Center.x < 0.0f)
			{
				if (RC->GetBoundingSphere()->Center.x < MAP_XBEGd2)
				{
					vec0.push_back(RC);
				}
				else
				{
					vec1.push_back(RC);
				}
			}
			else
			{
				if (RC->GetBoundingSphere()->Center.x < MAP_XENDd2)
				{
					vec2.push_back(RC);
				}
				else
				{
					vec3.push_back(RC);
				}
			}
		}
		std::sort(vec.begin(), vec.end(), __SortByY());
		//std::atomic<uint32_t> threads = 4u;
		
		std::thread t0(sortPy, vec0.begin(), vec0.end());
		std::thread t1(sortPy, vec1.begin(), vec1.end());
		std::thread t2(sortPy, vec2.begin(), vec2.end());
		std::thread t3(sortPy, vec3.begin(), vec3.end());

		t0.join();
		t1.join();
		t2.join();
		t3.join();


		vec0.clear();
		vec1.clear();
		vec2.clear();
		vec3.clear();
		//m_async--;
	}

	void SortByX(std::vector<RenderContainer*> &vec) noexcept
	{
		std::sort(vec.begin(), vec.end(), __SortByX());
		//m_async--;
	}

	inline void DoNothing() noexcept
	{
		//ipp::Console::Print("!");
	}



	bool _vectorcall validateRendering(XMFLOAT3 object) noexcept
	{
		float f[2] = { abs((object.x) - (m_cameraPosition.m128_f32[0])),abs((object.y) - (m_cameraPosition.m128_f32[1])) };

		if ((f[0] > m_ranges[0]) || (f[1] > m_ranges[1]))
		{
			return false;
		}
		else
		{
			return true;
		}

	}

}

	void RendererManager::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
	{
		

			m_map->Render(deviceContext, viewMatrix, projectionMatrix, m_cameraPosition);

			GRAPHICS EnableAlphaBlending(true);

			m_unitsShader->Begin(deviceContext);
			
			g_units.Render(deviceContext, viewMatrix, projectionMatrix, m_unitsShader);
			
			m_unitsShader->End(deviceContext);


			m_shader->Begin(deviceContext);

			m_ui->Render(deviceContext, viewMatrix, projectionMatrix);


			m_shader->End(deviceContext);

			GRAPHICS EnableAlphaBlending(false);
}

	extern "C"
	{

		void _vectorcall UpdatePart(std::vector<RenderContainer*> vec,float dt) noexcept
		{
			RenderContainer** m_array = vec.data();
			for (uint32_t i = 0u; i < vec.size(); ++i)
			{
				m_array[i]->Update(dt);
			}
			//m_async--;

		}
	}

void RendererManager::Update()
{
#pragma region
	using std::async;
	using std::vector;
	using std::advance;
	using std::sort;
#pragma endregion
	m_cameraPosition = CAMERA GetPosition();
	m_ui->Update(m_cameraPosition);
	float dt = ipp::Timer::GetDeltaTime();
	m_map->Update(dt);

	if (m_engine->GetGameStance() == false)
	{
		g_units.Update(dt);
	}

			
	g_units.Sort();	

}



void RendererManager::SetRenderingStyle(RenderingStyle render)
{
	m_renderingStyle = render;
}

void RendererManager::SetInterface(uint32_t type,Shader* shader)
{
	m_ui->SetScene(type, shader);
}

void RendererManager::SetTile(XMFLOAT2 position, int32_t tile)
{
	m_map->SetTile(position, tile);
}

void RendererManager::SaveInstanceToFile(std::string filename)
{
	m_map->SaveToFile(filename);
}

void RendererManager::LoadInstanceToFile(std::string filename)
{
	m_map->LoadFromFile(filename);
}

std::stack<Unit*> _vectorcall RendererManager::GetUnitsInRange(Unit * object, float range) noexcept
{
	return g_units.GetUnitsInRange(object, range);
}

RendererManager * RendererManager::GetInstance()
{
	return m_instance;
}

size_t RendererManager::GetNumberOfObjects()
{
	return g_units.GetSize();
}

RenderContainerVector::RenderContainerVector()
{
	m_objects.reserve(20000u);
}

void RenderContainerVector::Update(float dt)
{
	//m_async = 2u;
//	size_t middle = m_objects.size() / 2u;
//	vector<RenderContainer*>::const_iterator middle_iter(m_objects.cbegin());
	//vector<RenderContainer*>::const_iterator twofour(m_objects.cbegin());
	//vector<RenderContainer*>::const_iterator threefour(m_objects.cbegin());
//	advance(middle_iter, middle);
	//advance(twofour, middle * 2u);
	//advance(threefour, middle * 3u);
	//vector<RenderContainer*> t1(m_objects.cbegin(), middle_iter);
	//vector<RenderContainer*> t2(middle_iter, m_objects.cend());
	//vector<RenderContainer*> t3(twofour, threefour);
	//vector<RenderContainer*> t4(threefour, m_objects.cend());
	//thread tt1(UpdatePart, t1, dt);
//	thread tt2(UpdatePart, t2, dt);
	//thread tt3(UpdatePart, t3, dt);
	//thread tt4(UpdatePart, t4, dt);
	////async(launch::async, UpdatePart, t1, dt);
	////async(launch::async, UpdatePart, t2, dt);
	////async(launch::async, UpdatePart, t3, dt);
	////async(launch::async, UpdatePart, t4, dt);
	////while (m_async)
	////{
	////	DoNothing();
	////}
	//tt1.join();
	//tt2.join();
	//tt3.join();
	//tt4.join();
	UpdatePart(m_objects, dt);
}

void RenderContainerVector::Sort()
{
	//m_async = 2u;
	//std::async(std::launch::async,SortByX,(m_objects));
	//std::async(std::launch::async,SortByY,(m_objects));
	//SortByX(m_objects);
   // SortByY(m_objects);
	//while (m_async)
	//{
	//	DoNothing();
	//}

	std::sort(m_objects.begin(), m_objects.end(), __SortByX());
	std::sort(m_objects.begin(), m_objects.end(), __SortByY());

	//int (_cdecl)
	//std::qsort(m_objects.data(), m_objects.size(), sizeof(RenderContainer*), CollisionSortingXY);

	//std::sort(m_objects.begin(), m_objects.end(), CollisionSortingXY);
}

static uint32_t sizeg = 0u;

void _vectorcall RenderContainerVector::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader * shader) noexcept
{
	RenderContainer** objects = m_objects.data();
	for (uint32_t i = 0; i < (uint32_t)m_objects.size(); i++)
	{
		objects[i]->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		objects[i]->m_index = i;
	}
}

void RenderContainerVector::Clear()
{
	for (auto &&object : m_objects)
	{
		if (object)
		{
		//	delete object;
			object->Release();
			object = nullptr;
		}
	}
	m_objects.clear();

}

void RenderContainerVector::Push(Unit * unit)
{
	m_objects.push_back(unit);
}

void RenderContainerVector::Push(Doodads * doodads)
{
	m_objects.push_back(doodads);
}

void RenderContainerVector::Push(AnimatedDoodads* animated)
{
	m_objects.push_back(animated);
}

void RenderContainerVector::Push(Tree * tree)
{
	m_objects.push_back(tree);
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

void _stdcall PushUnitsInRange(std::vector<RenderContainer*>* vec,atomic<std::stack<Unit*>*>* sa, RenderContainer* object, float range) noexcept
{
	for (auto unit : *vec)
	{
		if (unit&&unit != object&&(unit->m_type == RenderContainer::RenderContainerType::UNIT))
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
	m_async--;
	return;
}

std::stack<Unit*> _vectorcall RenderContainerVector::GetUnitsInRange(Unit* object, float range) noexcept
{
	std::stack<Unit*> units;
	atomic<std::stack<Unit*>*> sa = &units;
	std::vector<RenderContainer*>* upv = &g_units.m_zVectors[(int8_t)object->GetZ()]->m_objects;
	size_t index = (size_t)object->m_index;
	
	std::vector<RenderContainer*> fv(upv->begin(), upv->begin() + index);
	std::reverse(fv.begin(), fv.end());
	std::vector<RenderContainer*> sv(upv->begin() + index, upv->end());
	m_async = 2;
	std::async(std::launch::async, PushUnitsInRange, &fv, &sa, object, range);
	std::async(std::launch::async, PushUnitsInRange, &sv, &sa, object, range);
	while (m_async)
	{
		DoNothing();
	}
			return units;
}

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
		vector.second->Render(deviceContext,viewMatrix,projectionMatrix,shader);
	}
}

void RenderZMap::Clear()
{
	for (auto vector : m_zVectors)
	{
		vector.second->Clear();
	}
}

void RenderZMap::Push(Unit * unit,int8_t z)
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
		size += (uint32_t)vector.second->m_objects.size();
	}
	return size;
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
