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


class Unit;

namespace
{
	RendererManager*              m_instance;
	Engine*                       m_engine;
	static XMVECTOR               m_cameraPosition;
	static float                  m_rangeX;
	static float                  m_rangeY;
	static RenderZMap             g_units;
	static atomic<int32>          m_cleanupMode;
}

void _cdecl CleanupFrame()
{
	m_cleanupMode.store(1, std::memory_order::memory_order_seq_cst);
}

RendererManager::RendererManager(
	class Engine* const engine,
	class Shader* const units,
	class Shader* const ui,
	class Shader* const shadow,
	class Shader* const select
) :
	m_engine(engine),
	m_unitsShader(units),
	m_shader(ui),
	m_shadowShader(shadow),
	m_selectShader(select)
{

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
		m_ui = nullptr;
	}
	if (m_map)
	{
		delete m_map;
		m_map = nullptr;
	}
}



void RendererManager::PushUnit(
	class Unit * const unit,
	const int32 z
)
{
	g_units.Push(unit,z);
}

void RendererManager::PushDoodads(class Doodads * doodads,const int32 z)
{
	g_units.Push(doodads,z);
}

void RendererManager::PushAnimatedDoodads(class AnimatedDoodads * doodads,const int32 z)
{
	g_units.Push(doodads,z);
}

void RendererManager::PushTree(class Tree * doodads,const int32 z)
{
	g_units.Push(doodads,z);
}




	int32 _vectorcall validateRendering(const struct XMFLOAT3& object) noexcept
	{
		const float x = abs((object.x) - (m_cameraPosition.m128_f32[0]));
		const float y = abs((object.y) - (m_cameraPosition.m128_f32[1]));

		if ((x > m_rangeX) || (y > m_rangeY))
			return 0;
		else return 1;

	}


	void RendererManager::Render(
		struct ID3D11DeviceContext * const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix
	)
	{
		struct ShaderPackage pck;
		pck.m_context = deviceContext;
		pck.select = m_selectShader;
		pck.shadow = m_shadowShader;
		pck.standard = m_unitsShader;

		
		GRAPHICS EnableAlphaBlending(true);
			m_map->Render(deviceContext, viewMatrix, projectionMatrix, m_cameraPosition);

			

			//m_unitsShader->Begin(deviceContext);
			
			g_units.Render(deviceContext, viewMatrix, projectionMatrix, pck);
			
			//m_unitsShader->End(deviceContext);


			m_shader->Begin(deviceContext);

			m_ui->Render(deviceContext, viewMatrix, projectionMatrix);


			m_shader->End(deviceContext);

}

void RendererManager::Update()
{
	m_cameraPosition = CAMERA GetPosition();
	m_ui->Update(m_cameraPosition);
	const float dt = ipp::Timer::GetDeltaTime();
	m_map->Update(dt);

	if (m_engine->GetGameStance() == false)
	{
		if (m_cleanupMode.load(std::memory_order::memory_order_seq_cst) == 1)
		{
			g_units.CleanUp();
			m_cleanupMode.store(0, std::memory_order::memory_order_seq_cst);
		}
		g_units.Update(dt);
	}

	g_units.Sort();	

}




void RendererManager::SetInterface(const uint32 type,class Shader* shader)
{
	m_ui->SetScene(type, shader);
}

void RendererManager::SetTile(XMFLOAT2 position,const int32 tile)
{
	m_map->SetTile(position, tile);
}

void RendererManager::SetTile(XMFLOAT2 position,const int32 tile,const int32 brush)
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

std::stack<Unit*> _vectorcall RendererManager::GetUnitsInRange(class Unit * const object,const float range) noexcept
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

std::vector<int64> RendererManager::GetNumberOfObjectsVector()
{
	return g_units.GetSizeVector();
}




