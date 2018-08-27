#include "RendererManager.h"
#include "Onion.h"
#include "SettingsC.h"
#include "Defines.h"
#include <future>
#include <mutex>

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
}

RendererManager::RendererManager(Engine* engine,Shader* shader)
{
	this->m_renderingStyle = RendererManager::RenderingStyle::REVERSE;
	this->m_engine = engine;
	m_instance = this;
	this->m_shader = shader;
	Tile::SetGlobals(Engine::GetEngine()->GetGraphics()->GetDevice(), shader,this);
	m_map.Initialize();
	m_ui = new UserInterface();
	m_ranges[0] = ((float)*(SETTINGS RESOLUTION_X) / 2.0f)+100.0f;
	m_ranges[1] = ((float)*(SETTINGS RESOLUTION_Y) / 2.0f) + 100.0f;
}


RendererManager::~RendererManager()
{
	RemoveAllObjects();
	if (m_ui)
	{
		delete m_ui;
		m_ui = NULL;
	}
}

void RendererManager::PushModel(Model * model)
{
	//RenderObject object;
	//object.SetRenderType(MODEL);
	//object.m_model = model;
	//m_objects.push_back(model);
}

void RendererManager::PushBox(CollisionBox * box)
{
	//RenderObject object;
	//object.SetRenderType(BOX);
	//object.m_box = box;
	//m_objects.push_back(object);
}

void RendererManager::PushUnit(Unit * unit)
{
	//RenderObject object;
	//object.SetRenderType(UNIT);
	//object.m_unit = unit;
	m_objects.push_back(unit);
}

extern "C"
{

	struct SortByY {
		bool operator()(Unit* a, Unit* b) const noexcept {

			float ax = 0.0f, ay = 0.0f;
			float bx = 0.0f, by = 0.0f;
			float radius = 0.0f;
			float distance = 0.0f;
			float distanceX = 0.0f, distanceY = 0.0f;
			float collision = 0.0f;

			
				if (a->m_model->m_flags[0])
				{
					ax = a->m_model->Center.x;
					ay = a->m_model->Center.y;
					radius = a->m_model->Radius;
				}
			
				if (b->m_model->m_flags[0])
				{
					bx = b->m_model->Center.x;
					by = b->m_model->Center.y;
					radius += b->m_model->Radius;
				}
				else return true;
			
			distanceX = ax - bx;
			distanceY = ay - by;
			distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
			if (distance < radius)
			{
				collision = distance - radius;
				if (a->m_model->m_flags[2])
				{
					if (b->m_model->m_flags[2])
					{
						collision /= 2.0f;
						if (ax < bx)
						{
							a->m_model->Center.x += collision;
								b->m_model->Center.x -= collision;
						}
						else
						{
							a->m_model->Center.x -= collision;
							a->m_model->Center.x += collision;

						}
						a->m_model->UpdatePosition();
						b->m_model->UpdatePosition();
					}
					else
					{
						if (ax < bx) a->m_model->Center.x += collision;
						else         a->m_model->Center.x -= collision;

						a->m_model->UpdatePosition();
					}
				}
				else
				{
					if (b->m_model->m_flags[2])
					{
						if (ax < bx) b->m_model->Center.x -= collision;
						else         b->m_model->Center.x += collision;


						b->m_model->UpdatePosition();
					}
					else
					{

					//	a.GoBack();
					//	b.GoBack();
					}
				}
			//	a.Block();
			//	b.Block();
			}
			else
			{
				//a.Block(false);
				//b.Block(false);
			}
			return ay > by;
		}
	};

	struct SortByX {
		bool operator()(Unit *a, Unit *b) const noexcept {

			float ax = 0.0f, ay = 0.0f;
			float bx = 0.0f, by = 0.0f;
			float radius = 0.0f;
			float distance = 0.0f;
			float distanceX = 0.0f, distanceY = 0.0f;
			float collision = 0.0f;

			
				if (a->m_model->m_flags[0])
				{
					ax = a->m_model->Center.x;
					ay = a->m_model->Center.y;
					radius = a->m_model->Radius;
				}
				
				if (b->m_model->m_flags[0])
				{
					bx = b->m_model->Center.x;
					by = b->m_model->Center.y;
					radius += b->m_model->Radius;
				}
				
			distanceX = ax - bx;
			distanceY = ay - by;
			distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
			if (distance < radius)
			{
				collision = distance - radius;
				if (a->m_model->m_flags[2])
				{
					if (b->m_model->m_flags[2])
					{
						collision /= 2.0f;
						if (ay < by)
						{
							a->m_model->Center.y += collision;
							b->m_model->Center.y -= collision;

						}
						else
						{
							a->m_model->Center.y -= collision;
							b->m_model->Center.y += collision;

						}
					}
					else
					{
						if (ay < by) a->m_model->Center.y += collision;
						else         a->m_model->Center.y -= collision;

					}
				}
				else
				{
					if (b->m_model->m_flags[2])
					{
						if (ay < by) b->m_model->Center.y -= collision;
						else         b->m_model->Center.y += collision;
					}

				}

			}

			return ax > bx;
		}
	};

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
		
		m_shader->Begin(deviceContext);
		GRAPHICS EnableAlphaBlending(true);
		m_map.Render(deviceContext, viewMatrix, projectionMatrix,m_cameraPosition);

		for (auto &&object : m_objects)
		{
					object->GetModel()->Render(deviceContext, viewMatrix, projectionMatrix, m_shader);
		}
		m_ui->Render(deviceContext, viewMatrix, projectionMatrix);


GRAPHICS EnableAlphaBlending(false);
m_shader->End(deviceContext);
}

	extern "C"
	{

		void _vectorcall UpdatePart(std::vector<Unit*> vec,float dt) noexcept
		{
			int mousePosition[2];
			UserInterface::GetMousePosition(mousePosition[0],mousePosition[1]);
			FXMVECTOR point = XMVectorSet((float)mousePosition[0], (float)mousePosition[1], 0.0f, 0.0f);
			for (auto unit : vec)
			{

						
						Model* model = unit->GetModel();
						unit->Update();
						model->Update(dt);
						model->SetRenderingStance(validateRendering(model->GetPosition()));
						if (model->Contains(point))
						{
							model->GoBack();
							if (model->Contains(point))
							{
								model->m_flags[1] = true;
								//GLOBAL m_lastSelectedUnit = (*i);
							}
							else
							{
								model->m_flags[1] = false;
							}
						}
						else
						{
							model->m_flags[1] = false;
						}
						
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

	if (m_engine->GetGameStance() == false)
	{
		std::reverse(m_objects.begin(), m_objects.end());
		UpdatePart(m_objects, dt);
	}

			

		sort(m_objects.begin(), m_objects.end(), SortByX());
		sort(m_objects.begin(), m_objects.end(), SortByY());

	

}

void RendererManager::RemoveAllObjects()
{
	for (auto &&object : m_objects)
	{
			delete object;
			object = nullptr;
	}
	m_objects.clear();
}

void RendererManager::SetRenderingStyle(RenderingStyle render)
{
	m_renderingStyle = render;
}

void RendererManager::SetInterface(unsigned int type,Shader* shader)
{
	m_ui->SetScene(type, shader);
}

RendererManager * RendererManager::GetInstance()
{
	return m_instance;
}


