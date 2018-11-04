#include "RendererManager.h"
#include "IPP.h"
#include "SettingsC.h"
#include "Defines.h"
#include "ShadowShader.h"
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
	static atomic<int32_t>            m_coord[2];
	atomic<uint8_t>               m_async;
	static RenderZMap             g_units;
	//std::mutex                    m_validateMutex;
}

RendererManager::RendererManager(Engine* engine,Shader* units,Shader* ui,Shader* shadow)
{
	this->m_renderingStyle = RendererManager::RenderingStyle::REVERSE;
	this->m_engine = engine;
	this->m_unitsShader = units;
	this->m_shader = ui;
	this->m_shadowShader = shadow;




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

			m_shadowShader->Begin(deviceContext);

			g_units.Render(deviceContext, viewMatrix, projectionMatrix, m_shadowShader);

			m_shadowShader->End(deviceContext);

			m_unitsShader->Begin(deviceContext);
			
			g_units.Render(deviceContext, viewMatrix, projectionMatrix, m_unitsShader);
			
			m_unitsShader->End(deviceContext);


			m_shader->Begin(deviceContext);

			m_ui->Render(deviceContext, viewMatrix, projectionMatrix);


			m_shader->End(deviceContext);

			GRAPHICS EnableAlphaBlending(false);
}

void RendererManager::Update()
{
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

void RendererManager::SetTile(XMFLOAT2 position, int32_t tile, int32_t brush)
{
	if(brush)
	m_map->SetTile(position, tile,brush);
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

__m128 RendererManager::GetNumberOfObjectsX4()
{
	return g_units.GetSizeX4();
}

std::vector<uint32_t> RendererManager::GetNumberOfObjectsVector()
{
	return g_units.GetSizeVector();
}




