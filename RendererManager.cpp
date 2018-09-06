#include "RendererManager.h"
#include "Onion.h"
#include "SettingsC.h"
#include "Defines.h"
#include <future>
#include <mutex>
#include <stack>

using Onion::Timer;
using std::mutex;

#pragma region
class Unit;
#define UnitPtr Unit*;
#pragma endregion

namespace
{
	RendererManager*    m_instance;
	Engine*             m_engine;
	static XMVECTOR     m_cameraPosition;
	static float        m_ranges[2];
	static atomic<int>  m_coord[2];
	atomic<uint8_t>     m_async;
	static UnitsVector  g_units;
}

RendererManager::RendererManager(Engine* engine,Shader* shader)
{
	this->m_renderingStyle = RendererManager::RenderingStyle::REVERSE;
	this->m_engine = engine;
	m_instance = this;
	this->m_shader = shader;
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



void RendererManager::PushUnit(Unit * unit)
{
	g_units.Push(unit);
}

extern "C"
{
	struct __SortByY {
		bool operator()(Unit* a, Unit* b) const noexcept {

			float ax = 0.0f, ay = 0.0f;
			float bx = 0.0f, by = 0.0f;
			float radius = 0.0f;
			float distance = 0.0f;
			float distanceX = 0.0f, distanceY = 0.0f;
			float collision = 0.0f;



			if (a->m_flags[0])
			{
				ax = a->Center.x;
				ay = a->Center.y;
				radius = a->Radius;
			}

			if (b->m_flags[0])
			{
				bx = b->Center.x;
				by = b->Center.y;
				radius += b->Radius;
			}


			distanceX = ax - bx;
			distanceY = ay - by;
			distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
			if (distance < radius)
			{
				collision = distance - radius;
				if (a->m_flags[2])
				{
					if (b->m_flags[2])
					{
						collision /= 2.0f;
						if (ax < bx)
						{
							a->Center.x += collision;
							b->Center.x -= collision;
						}
						else
						{
							a->Center.x -= collision;
							a->Center.x += collision;

						}
						//a->UpdatePosition();
						//b->UpdatePosition();
					}
					else
					{
						if (ax < bx) a->Center.x += collision;
						else         a->Center.x -= collision;

						//a->UpdatePosition();
					}
				}
				else
				{
					if (b->m_flags[2])
					{
						if (ax < bx) b->Center.x -= collision;
						else         b->Center.x += collision;


						//b->UpdatePosition();
					}

				}

			}

			return ay > by;
		}
	};

	struct __SortByX {
		bool operator()(Unit *a, Unit *b) const noexcept {

			float ax = 0.0f, ay = 0.0f;
			float bx = 0.0f, by = 0.0f;
			float radius = 0.0f;
			float distance = 0.0f;
			float distanceX = 0.0f, distanceY = 0.0f;
			float collision = 0.0f;



			if (a->m_flags[0])
			{
				ax = a->Center.x;
				ay = a->Center.y;
				radius = a->Radius;
			}

			if (b->m_flags[0])
			{
				bx = b->Center.x;
				by = b->Center.y;
				radius += b->Radius;
			}

			distanceX = ax - bx;
			distanceY = ay - by;
			distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
			if (distance < radius)
			{
				collision = distance - radius;
				if (a->m_flags[2])
				{
					if (b->m_flags[2])
					{
						collision /= 2.0f;
						if (ay < by)
						{
							a->Center.y += collision;
							b->Center.y -= collision;
						}
						else
						{
							a->Center.y -= collision;
							b->Center.y += collision;
						}
					}
					else
					{
						if (ay < by) a->Center.y += collision;
						else         a->Center.y -= collision;

					}
				}
				else
				{
					if (b->m_flags[2])
					{
						if (ay < by) b->Center.y -= collision;
						else         b->Center.y += collision;
					}

				}

			}

			return ax > bx;
		}
	};

	void _stdcall SortByY(std::vector<Unit*> &vec) noexcept
	{
		std::sort(vec.begin(), vec.end(), __SortByY());
		m_async--;
	}

	void _stdcall SortByX(std::vector<Unit*> &vec) noexcept
	{
		std::sort(vec.begin(), vec.end(), __SortByX());
		m_async--;
	}

	inline void DoNothing() noexcept
	{

	}



	bool _vectorcall validateRendering(XMFLOAT3 object) noexcept
	{
		float f[2];
		f[0] = abs((object.x) - (m_cameraPosition.m128_f32[0]));
		f[1] = abs((object.y) - (m_cameraPosition.m128_f32[1]));
		if ((f[0] > m_ranges[0])||(f[1] > m_ranges[1]))
			return false;
		else return true;
	}

}

	void RendererManager::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
	{
		
		
		m_map->Render(deviceContext, viewMatrix, projectionMatrix,m_cameraPosition);
		m_shader->Begin(deviceContext);
		GRAPHICS EnableAlphaBlending(true);
		g_units.Render(deviceContext, viewMatrix, projectionMatrix, m_shader);
		m_ui->Render(deviceContext, viewMatrix, projectionMatrix);


GRAPHICS EnableAlphaBlending(false);
m_shader->End(deviceContext);
}

	extern "C"
	{

		void _vectorcall UpdatePart(std::vector<Unit*> vec,float dt) noexcept
		{
			Unit** m_array = vec.data();
			for (uint32_t i = 0u; i < vec.size(); ++i)
			{
				m_array[i]->Update(dt);
			}


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
	float dt = Timer::GetDeltaTime();
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

void RendererManager::SetInterface(unsigned int type,Shader* shader)
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

RendererManager * RendererManager::GetInstance()
{
	return m_instance;
}

void UnitsVector::Update(float dt)
{
	UpdatePart(m_objects, dt);
}

void UnitsVector::Sort()
{
	m_async = 2u;
	std::async(std::launch::async,SortByX,(m_objects));
	std::async(std::launch::async,SortByY,(m_objects));
	while (m_async)
	{
		DoNothing();
	}
	SortByX(m_objects);
	SortByY(m_objects);
}

static uint32_t sizeg = 0u;

void UnitsVector::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader * shader)
{
	Unit** objects = m_objects.data();
	sizeg = (uint32_t)m_objects.size();
	for (uint32_t i = 0; i < sizeg; i++)
	{
		objects[i]->Render(deviceContext, viewMatrix, projectionMatrix, shader);
		objects[i]->m_index = i;
	}
}

void UnitsVector::Clear()
{
	for (auto &&object : m_objects)
	{
		if (object)
		{
			delete object;
			object = nullptr;
		}
	}
	m_objects.clear();

}

void UnitsVector::Push(Unit * unit)
{
	m_objects.push_back(unit);

}

bool _stdcall CheckDistance(Unit* a, Unit* b, float range) noexcept
{
float distanceX = a->Center.x - b->Center.x;
float distanceY = a->Center.y - b->Center.y;
float distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
if (distance < range)
	return true; else return false;
}

void _stdcall PushUnitsInRange(std::vector<Unit*>* vec,atomic<std::stack<Unit*>*>* sa,Unit* object, float range)
{
	for (auto unit : *vec)
	{
		if (unit&&unit != object)
		{
			if (CheckDistance(unit, object, range))
			{
				sa->load()->push(unit);
			}
			else
			{
				break;
			}
		}
	}
	m_async--;
}

std::stack<Unit*> UnitsVector::GetUnitsInRange(Unit* object, float range)
{
	//Whoops::Stack units;
	std::stack<Unit*> units;
	atomic<std::stack<Unit*>*> sa = &units;
	std::vector<Unit*>* upv = &g_units.m_objects;
	size_t index = (size_t)object->m_index;
	
	std::vector<Unit*> fv(upv->begin(), upv->begin() + index);
	std::reverse(fv.begin(), fv.end());
	std::vector<Unit*> sv(upv->begin() + index, upv->end());
	m_async = 2;
	std::async(std::launch::async, PushUnitsInRange, &fv, &sa, object, range);
	std::async(std::launch::async, PushUnitsInRange, &sv, &sa, object, range);
	while (m_async)
	{
		DoNothing();
	}
	//for (auto unit : fv)
	//{
	//	if (unit&&unit != object)
	//	{
	//		if(CheckDistance(unit, object, range))
	//		{
	//			sa.load()->push(unit);
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}
	//
	//for (auto unit : sv)
	//{
	//	if (unit&&unit!=object)
	//	{
	//		if (CheckDistance(unit, object, range))
	//		{
	//			sa.load()->push(unit);
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}

			return units;

	
}

