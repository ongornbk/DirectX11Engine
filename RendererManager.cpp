#include "RendererManager.h"
#include "IPP.h"
#include "SettingsC.h"
#include "Defines.h"
#include "ShadowShader.h"
#include "Global.h"
#include "ShaderPackage.h"
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
	static float                  m_rangeX;
	static float                  m_rangeY;
	static RenderZMap             g_units;
}

RendererManager::RendererManager(Engine* engine,Shader* units,Shader* ui,Shader* shadow,Shader* select)
{
	this->m_engine = engine;
	this->m_unitsShader = units;
	this->m_shader = ui;
	this->m_shadowShader = shadow;
	this->m_selectShader = select;




	m_instance = this;
	
	Tile::SetGlobals(Engine::GetEngine()->GetGraphics()->GetDevice(), GETSHADER "tile.fx" CLOSE,this);
	m_map = new TileMap(1.0f,1.0f,0.2f,true);
	m_map->Initialize();
	TileMap::SetCurrentTileMap(m_map);
	Tile::SetDeviceContext(Engine::GetEngine()->GetGraphics()->GetDeviceContext());
	m_ui = new UserInterface();
	m_rangeX = ((float)(Settings::GetResolutionX()) / 2.0f)+300.0f;
	m_rangeY = ((float)(Settings::GetResolutionY()) / 2.0f) + 300.0f;

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




	bool _vectorcall validateRendering(XMFLOAT3 _In_ object) noexcept
	{
		float x = abs((object.x) - (m_cameraPosition.m128_f32[0]));
		float y = abs((object.y) - (m_cameraPosition.m128_f32[1]));

		if ((x > m_rangeX) || (y > m_rangeY))
		{
			return false;
		}
		else
		{
			return true;
		}

	}


	void RendererManager::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
	{
		ShaderPackage pck;
		pck.select = m_selectShader;
		pck.shadow = m_shadowShader;
		pck.standard = m_unitsShader;

			m_map->Render(deviceContext, viewMatrix, projectionMatrix, m_cameraPosition);

			GRAPHICS EnableAlphaBlending(true);

			m_unitsShader->Begin(deviceContext);
			
			g_units.Render(deviceContext, viewMatrix, projectionMatrix, pck);
			
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




