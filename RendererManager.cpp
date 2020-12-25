#include "RendererManager.h"
#include "IPP.h"
#include "SettingsC.h"
#include "Defines.h"
#include "ShadowShader.h"
#include "Global.h"
#include "ShaderPackage.h"
#include "GarbageCollector.h"
#include "RenderLayerCorpse.h"
#include "RenderLayerObject.h"
#include "RenderLayerShadow.h"

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
	//static RenderZMap             g_units;
	static atomic<int32>          m_cleanupMode;
	static atomic<int32>          m_editMode;
}

void _cdecl CleanupFrame()
{
	m_cleanupMode.store(1, std::memory_order::memory_order_seq_cst);
}

void _cdecl EditFrame()
{
	m_editMode.store(1, std::memory_order::memory_order_seq_cst);
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

	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_CORPSE_TYPE)] = new RenderLayerCorpse();
	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_OBJECT_TYPE)] = new RenderLayerObject();
	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_SHADOW_TYPE)] = new RenderLayerShadow();

}


RendererManager::~RendererManager()
{
	//g_units.Clear();
	//m_objects.Clear();
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

	for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
	{
		if (m_layers[i])
		{
			m_layers[i]->Clear();
			delete m_layers[i];
			m_layers[i] = nullptr;
		}
	}
}



void RendererManager::PushUnit(
	class Unit * const unit
)
{
	//m_objects.Push(unit);
	m_layers[enum_cast<int32_t>(unit->GetLayerType())]->Push(unit);
}

void RendererManager::PushDoodads(class Doodads * doodads)
{
	//m_objects.Push(doodads);
	m_layers[enum_cast<int32_t>(doodads->GetLayerType())]->Push(doodads);
}

void RendererManager::PushAnimatedDoodads(class AnimatedDoodads * doodads)
{
	//m_objects.Push(doodads);
	m_layers[enum_cast<int32_t>(doodads->GetLayerType())]->Push(doodads);
}

void RendererManager::PushTree(class Tree * tree)
{
	//m_objects.Push(tree);
	//EditFrame();
	m_layers[enum_cast<int32_t>(tree->GetLayerType())]->Push(tree);
}

void RendererManager::Push(class EObject* const object, const enum class RenderLayerType layer)
{
	m_layers[enum_cast<int32_t>(layer)]->Push(object);
}

void RendererManager::PushRegionPointObject(RegionPointObject* object)
{
	//m_objects.Push(object);
}




	const _Out_ int32 _stdcall validateRendering(const struct DirectX::XMFLOAT3& _In_ object) noexcept
	{
		const float x = abs((object.x) - (m_cameraPosition.m128_f32[0]));
		const float y = abs((object.y) - (m_cameraPosition.m128_f32[1]));

		if ((x > m_rangeX) || (y > m_rangeY))
			return 0;
		else return 1;

	}


	void RendererManager::Render(
		struct ID3D11DeviceContext* const deviceContext,
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
			
			//m_objects.Render(deviceContext, viewMatrix, projectionMatrix, pck);

			for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
			{
				m_layers[i]->Render(deviceContext, viewMatrix, projectionMatrix, pck);
			}

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

	//switch (m_editMode.load())
	//{
	//case 0:
	//{
		if (m_engine->GetGameStance() == false)
		{
			if (m_cleanupMode.load(std::memory_order::memory_order_seq_cst) == 1)
			{
				//m_objects.CleanUp();

				for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
				{
					m_layers[i]->CleanUp();
				}

				m_cleanupMode.store(0, std::memory_order::memory_order_seq_cst);
			}
			//g_units.Update(dt);
			//m_objects.Update(dt);

			for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
			{
				m_layers[i]->Update(dt);
			}

		}

		//g_units.Sort();
		//g_units.StaticSort();
		//break;
	//}
	//case 1:
	//{
	//	m_editMode.store(0, std::memory_order::memory_order_seq_cst);
		//m_objects.Sort();
		//m_objects.QSort();

		for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
		{
			m_layers[i]->Sort();
			m_layers[i]->QSort();
		}
	//	break;
	//}
	//}
	

}




void RendererManager::SetInterface(const uint32 type,class Shader* shader)
{
	m_ui->SetScene(type, shader);
}

void RendererManager::SetTile(struct DirectX::XMFLOAT2 &position,const int32 tile)
{
	m_map->SetTile(position, tile);
}

void RendererManager::SetTile(struct DirectX::XMFLOAT2 &position,const int32 tile,const int32 brush)
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

void RendererManager::SetTileMapRendering(const int64 render)
{
	if(m_map)
	m_map->SetRendering(render);
}

void RendererManager::SetFps(const int32 fps)
{
//	m_objects.UpdateFps(fps);
	UserInterfaceGame::SetFPS(fps);
}

std::stack<Unit*> _vectorcall RendererManager::GetUnitsInRange(class Unit * const object,const float range) noexcept
{
	//return std::stack<Unit*>();// m_objects.GetUnitsInRange(object, range);
	return m_layers[enum_cast<int32_t>(object->GetLayerType())]->GetUnitsInRange(object, range);
}

RendererManager * RendererManager::GetInstance()
{
	return m_instance;
}

size_t RendererManager::GetNumberOfObjects()
{
	//return m_objects.GetSize();
}

__m128 RendererManager::GetNumberOfObjectsX4()
{
//	return m_objects.GetSizeX4();
}

std::vector<int64> RendererManager::GetNumberOfObjectsVector()
{
//	return m_objects.GetSizeVector();
	return std::vector<int64>();
}




