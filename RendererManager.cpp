#pragma region
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
#include "RenderLayerItem.h"
#include "RenderLayerInterface.h"
#include "Timer.h"
#include "ActionApplyColorFilter.h"
#include "ActionExecuteActionArray.h"
#include "ActionSetShadowCast.h"
#include "ActionWaitUntil.h"
#include "ActionInitializeText.h"
#include "ActionTranslateText.h"
#include "ActionShowInterface.h"
#include "ConditionFactory.h"
#include "Options.h"
#include "ActionSetTextAlignment.h"
#include "ActionInitializeInterface.h"
#include "ActionSetInterfaceOffset.h"
#include "ActionTreeSetStance.h"
#include "RectOfCollisionAgentFirst.h"
#include "RectOfCollisionAgentSecond.h"
#include "InterfaceStatusBarBehavior.h"
#include "ActionSetInterfaceBehavior.h"
#include "TaskUpdateInterface_v0.h"
#include "TaskUpdateInteface_v1.h"
#include "TaskUpdateInterface_v2.h"
#include "TaskUpdateInterface_v3.h"
#include "TaskUpdateInterface_v4.h"
#include "TaskUpdateInterface_v5.h"
#include "TaskPack.h"
#include "RegionAgent.h"
#include "RegionAgentMaster.h"
#include "MPManager.h"
#pragma endregion
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
	static modern_handle          m_activeOptions;
}

void _cdecl CleanupFrame()
{
	m_cleanupMode.store(1, std::memory_order::memory_order_seq_cst);
}

void _cdecl EditFrame()
{
	m_editMode.store(1, std::memory_order::memory_order_seq_cst);
}

//EXECUTED AFTER LUA::ENGINE_INITIALIZATION
RendererManager::RendererManager(
	class Engine* const engine,
	class Shader* const units,
	class Shader* const ui,
	class Shader* const shadow,
	class Shader* const select,
	class Shader* const inter,
	class Shader* const text
) :
	m_engine(engine),
	m_unitsShader(units),
	m_shader(ui),
	m_shadowShader(shadow),
	m_selectShader(select),
	m_interfaceShader(inter),
	m_textShader(text),
	m_collision(false),
	//m_fpsText(nullptr),
	//m_objectsText(nullptr),
	m_fps(0)
{

	m_instance = this;
	new Options();
	m_activeOptions.make_handle(Options::GetInstance());

	Timer::Initialize();

	
	
	
	m_map = new TileMap(1.0f,1.0f,0.2f,true);
	m_map->Initialize();
	TileMap::SetCurrentTileMap(m_map);
	Tile::SetGlobals(Engine::GetEngine()->GetGraphics()->GetDevice(), GETSHADER "tile.fx" CLOSE, GETSHADER "blendtile.fx" CLOSE, this);
	Tile::SetDeviceContext(Engine::GetEngine()->GetGraphics()->GetDeviceContext());
	m_ui = new UserInterface();
	m_rangeX = ((float)(Settings::GetResolutionX()) / 2.0f) + 300.0f;
	m_rangeY = ((float)(Settings::GetResolutionY()) / 2.0f) + 300.0f;

	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_CORPSE_TYPE)]    = new class RenderLayerCorpse();
	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_OBJECT_TYPE)]    = new class RenderLayerObject();
	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_SHADOW_TYPE)]    = new class RenderLayerShadow();
	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_ITEM_TYPE)]      = new class RenderLayerItem();
	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_INTERFACE_TYPE)] = new class RenderLayerInterface();

	

	LetterSprite::SetMatrixIdentity(DirectX::XMMatrixIdentity());

	m_font = TextFont::GetFontByName("ExocetLight");
	m_font->Initialize(engine->GetGraphics()->GetDevice(), engine->GetGraphics()->GetDeviceContext(),m_textShader);

	class Agent* const agent_cursor = new class Agent();
	agent_cursor->Initialize(struct DirectX::XMFLOAT3(0.f, 0.f, 0.f));
	m_cursorAgent.make_handle(agent_cursor->GetHandle());


	class ActionExecuteActionArray* const marray = new ActionExecuteActionArray();

	marray->push(new ActionInitializeInterface(
		m_damage, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"damage"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(1920.f, 1080.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_CENTER
	));

	marray->push(new ActionInitializeText(
		m_fpsText,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_textShader,
		m_font, 24.f
	));

	marray->push(new ActionSetTextAlignment(m_fpsText,TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_fpsText,
		struct DirectX::XMFLOAT3(-935.f, 460.f, 0.f
		)));

	marray->push(new ActionInitializeText(
		m_bmapText,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_textShader,
		m_font, 24.f
	));

	marray->push(new ActionSetTextAlignment(m_bmapText, TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_bmapText,
		struct DirectX::XMFLOAT3(-935.f, 430.f, 0.f
		)));

	marray->push(new ActionInitializeText(
		m_heroPositionX,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_textShader,
		m_font, 24.f
	));

	marray->push(new ActionSetTextAlignment(m_heroPositionX, TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_heroPositionX,
		struct DirectX::XMFLOAT3(-935.f, 400.f, 0.f
		)));

	marray->push(new ActionInitializeText(
		m_heroPositionY,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_textShader,
		m_font, 24.f
	));

	marray->push(new ActionSetTextAlignment(m_heroPositionY, TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_heroPositionY,
		struct DirectX::XMFLOAT3(-935.f, 370.f, 0.f
		)));

	marray->push(new ActionInitializeText(
		m_objectsText,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_textShader,
		m_font, 24.f
	));

	marray->push(new ActionSetTextAlignment(m_objectsText, TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_objectsText,
		struct DirectX::XMFLOAT3(-935.f, 490.f, 0.f
		)));

	marray->push(new ActionInitializeText(
		m_timersText,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_textShader,
		m_font, 24.f
	));

	marray->push(new ActionSetTextAlignment(m_timersText, TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_timersText,
		struct DirectX::XMFLOAT3(-935.f, 520.f, 0.f
		)));

	marray->push(new ActionInitializeInterface(
		m_selectStatus, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"health_bar"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(200.f, 60.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_LEFT
	));

	marray->push(new ActionSetInterfaceOffset(
		m_selectStatus,
		struct DirectX::XMFLOAT3(0.f,0.f,0.f)
	));

	marray->push(new ActionSetInterfaceBehavior(
		m_selectStatus,
		new InterfaceStatusBarBehavior((class Interface* const)m_selectStatus.get())
	));

	marray->push(new ActionInitializeInterface(
		m_healthGlobe, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"health_globe"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(142.f, 142.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_BOTTOM
	));

	marray->push(new ActionSetInterfaceOffset(
		m_healthGlobe,
		struct DirectX::XMFLOAT3(-408.f, -463.f, 0.f)
	));

	marray->push(new ActionSetInterfaceBehavior(
		m_healthGlobe,
		new InterfaceStatusBarBehavior((class Interface* const)m_healthGlobe.get())
	));

	marray->push(new ActionShowInterface(
		m_healthGlobe,
		modern_false
	));

	marray->push(new ActionInitializeInterface(
		m_manaGlobe, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"mana_globe"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(138.f, 138.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_BOTTOM
	));

	marray->push(new ActionSetInterfaceOffset(
		m_manaGlobe,
		struct DirectX::XMFLOAT3(405.f, -460.f, 0.f)
	));

	marray->push(new ActionSetInterfaceBehavior(
		m_manaGlobe,
		new InterfaceStatusBarBehavior((class Interface* const)m_manaGlobe.get())
	));

	marray->push(new ActionShowInterface(
		m_manaGlobe,
		modern_false
	));

	marray->push(new ActionInitializeInterface(
		m_exp, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"ui_exp"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(644.f, 8.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_LEFT
	));

	marray->push(new ActionSetInterfaceOffset(
		m_exp,
		struct DirectX::XMFLOAT3(0.f, -476.f, 0.f)
	));

	marray->push(new ActionSetInterfaceBehavior(
		m_exp,
		new InterfaceStatusBarBehavior((class Interface* const)m_exp.get())
	));

	marray->push(new ActionShowInterface(
		m_exp,
		modern_false
	));

	marray->push(new ActionInitializeInterface(
		m_healthBar, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"health_bar_mini"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(80.f, 10.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_LEFT
	));

	marray->push(new ActionSetInterfaceOffset(
		m_healthBar,
		struct DirectX::XMFLOAT3(0.f, -476.f, 0.f)
	));

	marray->push(new ActionSetInterfaceBehavior(
		m_healthBar,
		new InterfaceStatusBarBehavior((class Interface* const)m_healthBar.get())
	));

	marray->push(new ActionInitializeInterface(
		m_healthBarBorder, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"health_bar_mini_border"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(80.f, 10.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_LEFT
	));

	marray->push(new ActionSetInterfaceOffset(
		m_healthBarBorder,
		struct DirectX::XMFLOAT3(0.f, -476.f, 0.f)
	));

	marray->push(new ActionInitializeInterface(
		m_selectStatusBorder, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"health_bar_border"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(200.f, 60.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_CENTER
	));

	marray->push(new ActionSetInterfaceOffset(
		m_selectStatusBorder,
		struct DirectX::XMFLOAT3(0.f, 500.f, 0.f)
	));

	marray->push(new ActionInitializeInterface(
		m_gameUI, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_textShader,
		class  modern_string(L"ui_game"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(1920.f, 175.f),
		ObjectAnchorType::OBJECT_ANCHOR_TYPE_CENTER
	));

	marray->push(new ActionSetInterfaceOffset(
		m_gameUI,
		struct DirectX::XMFLOAT3(0.f, -460.f, 0.f)
	));

	marray->push(new ActionShowInterface(
		m_gameUI,
		modern_false
	));
	

	Timer::CreateInstantTimer(marray);



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

	//if (m_fpsText)
	//{
	//	delete m_fpsText;
	//	m_fpsText = nullptr;
	//}
	//
	//if (m_objectsText)
	//{
	//	delete m_objectsText;
	//	m_objectsText = nullptr;
	//}
}



void RendererManager::PushUnit(
	class Unit * const unit
)
{
	m_layers[enum_cast<int32_t>(unit->GetLayerType())]->Push(unit);
}

void RendererManager::PushAgent(Agent* const agent)
{
	m_layers[enum_cast<int32_t>(agent->GetLayerType())]->Push(agent);
}

void RendererManager::PushProjectile(Projectile* const proj)
{
	m_layers[enum_cast<int32_t>(proj->GetLayerType())]->Push(proj);
}

void RendererManager::PushDoodads(class Doodads * doodads)
{
	m_layers[enum_cast<int32_t>(doodads->GetLayerType())]->Push(doodads);
}

void RendererManager::PushAnimatedDoodads(class AnimatedDoodads * doodads)
{
	m_layers[enum_cast<int32_t>(doodads->GetLayerType())]->Push(doodads);
}

void RendererManager::PushTree(class Tree * tree)
{
	m_layers[enum_cast<int32_t>(tree->GetLayerType())]->Push(tree);
}

void RendererManager::PushLineOfCollisionAgent(LineOfCollisionAgent* const agent)
{
	m_layers[enum_cast<int32_t>(agent->GetLayerType())]->Push(agent);
}

void RendererManager::PushRectOfCollisionAgent(RectOfCollisionAgentFirst* const agent)
{
	m_layers[enum_cast<int32_t>(agent->GetLayerType())]->Push(agent);
}

void RendererManager::PushRectOfCollisionAgent(RectOfCollisionAgentSecond* const agent)
{
	m_layers[enum_cast<int32_t>(agent->GetLayerType())]->Push(agent);
}

void RendererManager::PushRegionAgent(RegionAgent* const agent)
{
	m_layers[enum_cast<int32_t>(agent->GetLayerType())]->Push(agent);
}

void RendererManager::PushRegionAgentMaster(RegionAgentMaster* const agent)
{
	m_layers[enum_cast<int32_t>(agent->GetLayerType())]->Push(agent);
}

void RendererManager::PushRenderAgent(RenderAgent* const agent)
{
	//m_layers[enum_cast<uint64_t>(agent->GetLayerType())]->Push(agent);
	m_layers[1]->Push(agent);
}

void RendererManager::Push(class GameObject* const object, const enum class RenderLayerType layer)
{
	m_layers[enum_cast<int32_t>(layer)]->Push(object);
}

void RendererManager::PushRegionPointObject(RegionPointObject* object)
{
	m_layers[enum_cast<int32_t>(object->GetLayerType())]->Push(object);
}

void RendererManager::PushInterface(Interface* const object)
{
	m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_INTERFACE_TYPE)]->Push(object);
}




	const _Out_ int32 _stdcall validateRendering(const struct DirectX::XMFLOAT3& _In_ object) modern_except_state
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
		//MPManager::Get()->increment();
		this->Render(deviceContext, viewMatrix, projectionMatrix, projectionMatrix);
		//
	}
	


void RendererManager::Render(
	ID3D11DeviceContext* const deviceContext,
	const XMFLOAT4X4& viewMatrix,
	const XMFLOAT4X4& projectionMatrix,
	const XMFLOAT4X4& interfaceMatrix
)
{
	struct ID3D11Device* const device = Engine::GetEngine()->GetGraphics()->GetDevice();
	struct ShaderPackage pck(deviceContext, m_unitsShader, m_shadowShader, m_selectShader, m_interfaceShader,m_textShader);

	GRAPHICS EnableAlphaBlending(true);
	//MPManager::Get()->increment();

	m_map->Render(deviceContext, viewMatrix, projectionMatrix, m_cameraPosition);


	for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
	{
		m_layers[i]->Render(deviceContext, viewMatrix, projectionMatrix, pck);
	}



	pck.BeginInterface();
	GRAPHICS EnableAlphaBlending(true);

	switch (m_type)
	{
	case UserInterfaceState::ENUM_USERINTERFACE_GAME:
	{
		{
			class Interface* const A = (class Interface*)m_damage.get();
			if (A)
			{
				modern_guard g(A);
			//	A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
			}
		}
		{
			class Interface* const A = (class Interface*)m_exp.get();
			if (A)
			{
				modern_guard g(A);
				A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
			}
		}
		{
			class Interface* const A = (class Interface*)m_healthGlobe.get();
			if (A)
			{
				modern_guard g(A);
				A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
			}
		}
		{
			class Interface* const A = (class Interface*)m_manaGlobe.get();
			if (A)
			{
				modern_guard g(A);
				A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
			}
		}
		{
			class Interface* const A = (class Interface*)m_gameUI.get();
			if (A)
			{
				modern_guard g(A);
				A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
			}
		}
		
		break;
	}
	}

	//GRAPHICS EnableAlphaBlending(true);

	m_ui->Render(deviceContext, viewMatrix, interfaceMatrix);

	if (modern_Boolean_check ((Options*)m_activeOptions.get())->option_ShowFPS)
	{
		class Text* const A = (class Text* const)m_fpsText.get();
		if (A)
		{
			modern_guard g(A);
			A->PreRender(deviceContext, viewMatrix, interfaceMatrix, pck.BeginShadow());
			A->Render(deviceContext, viewMatrix, interfaceMatrix, pck.BeginInterface());

		}
		class Text* const D = (class Text* const)m_bmapText.get();
		if (D)
		{
			modern_guard g(D);
			D->PreRender(deviceContext, viewMatrix, interfaceMatrix, pck.BeginShadow());
			D->Render(deviceContext, viewMatrix, interfaceMatrix, pck.BeginInterface());

		}
		class Text* const B = (class Text* const)m_objectsText.get();
		if (B)
		{
			modern_guard g(B);
			B->PreRender(deviceContext, viewMatrix, interfaceMatrix, pck.BeginShadow());
			B->Render(deviceContext, viewMatrix, interfaceMatrix, pck.BeginInterface());
		}
		class Text* const C = (class Text* const)m_timersText.get();
		if (C)
		{
			modern_guard g(C);
			C->PreRender(deviceContext, viewMatrix, interfaceMatrix, pck.BeginShadow());
			C->Render(deviceContext, viewMatrix, interfaceMatrix, pck.BeginInterface());
		}
		class Text* const E = (class Text* const)m_heroPositionX.get();
		if (E)
		{
			modern_guard g(E);
			E->PreRender(deviceContext, viewMatrix, interfaceMatrix, pck.BeginShadow());
			E->Render(deviceContext, viewMatrix, interfaceMatrix, pck.BeginInterface());
		}
		class Text* const F = (class Text* const)m_heroPositionY.get();
		if (F)
		{
			modern_guard g(F);
			F->PreRender(deviceContext, viewMatrix, interfaceMatrix, pck.BeginShadow());
			F->Render(deviceContext, viewMatrix, interfaceMatrix, pck.BeginInterface());
		}
	}
	{
		class Interface* const A = (class Interface*)m_selectStatus.get();
		if (A)
		{
			modern_guard g(A);
			//A->PreRender(deviceContext, viewMatrix, projectionMatrix, pck.BeginShadow());
			//A->Render(deviceContext, viewMatrix, projectionMatrix, pck.BeginInterface());
			//A->m_flags.m_rendering = true;
			//A->PreRender(deviceContext, viewMatrix, projectionMatrix, pck);
			//A->PreRender(deviceContext, viewMatrix, interfaceMatrix, pck);
			//A->SetColorFilter(1.f);
			A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
		}
	}
	{
		class Interface* const A = (class Interface*)m_selectStatusBorder.get();
		if (A)
		{
			modern_guard g(A);
			//A->SetColorFilter(1.f);
			A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
		}
	}

	//{
	//	class Interface* const A = (class Interface*)m_cursor.get();
	//	if (A)
	//	{
	//		modern_guard g(A);
	//		//A->SetColorFilter(1.f);
	//		A->Render(deviceContext, viewMatrix, interfaceMatrix, pck);
	//	}
	//}

	//if (m_fpsText)
		//m_fpsText->Render(deviceContext, viewMatrix, projectionMatrix, pck.BeginInterface());
	//if (m_objectsText)
		//m_objectsText->Render(deviceContext, viewMatrix, projectionMatrix, pck.BeginInterface());

	//m_unitsShader->End(deviceContext);
	//TextFont* font = TextFont::GetFontByName("ExocetLight");
	//font->Initialize(device, deviceContext, pck.GetShader());
	//font.
	//LetterSprite* sp = font->GetSprite(nullptr, 'a');
	//sp->Update();
	//sp->Render(deviceContext, viewMatrix, projectionMatrix, pck.GetShader());

	//Text* text = new Text;
	//text->Initialize(device, deviceContext, pck.GetShader(), font, 20.f);
	//text->SetText("qwertyuiopasdfghjklzxcvbnmmnbvcxzlkjhgfdsapoiuytrewq");
	//text->SetPosition({ 0.f,0.f,0.f });
	//text->Update();
	//text->Render(deviceContext, viewMatrix, projectionMatrix, pck.GetShader());

	//m_shader->End(deviceContext);

	//m_shader->Begin(deviceContext);





	//GetDC()



	//Text t;
	////m_shader->Begin(deviceContext);
	//
	//t.Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), deviceContext, m_shader, font, 20.f);
	//t.SetText("baba");
	//t.SetPosition({ 0.f,0.f,0.f });
	//t.Update();
	//t.Render(deviceContext, viewMatrix, projectionMatrix,m_shader);



	pck.End();

	//pck.End();

	//MPManager::Get()->decrement();
}

	//static float updatetime = 0.f;

	void RendererManager::Update(const float dt,const bool renderframe)
	{

		GLOBAL release();

		m_cameraPosition = CAMERA GetPosition();
		m_ui->Update(m_cameraPosition);

		class MPManager* const mpm = MPManager::Get();
		//mpm->begin_weak_pushing();

		{
			class TaskPack* const pack = new TaskPack();

			switch (m_type)
			{
			case UserInterfaceState::ENUM_USERINTERFACE_GAME:
			{
				//mpm->weak_push(new TaskUpdateInterface_v0(m_gameUI,dt));
				//mpm->weak_push(new TaskUpdateInterface_v0(m_damage, dt));
				//mpm->weak_push(new TaskUpdateInterface_v1(m_exp, m_focus, dt));
			 //	  mpm->weak_push(new TaskUpdateInterface_v2(m_healthGlobe, m_focus, dt));
			//	  mpm->weak_push(new TaskUpdateInterface_v3(m_manaGlobe, m_focus, dt));
				//pack->pack(new TaskUpdateInterface_v0(m_gameUI, dt));
				//pack->pack(new TaskUpdateInterface_v0(m_damage, dt));
				//pack->pack(new TaskUpdateInterface_v1(m_exp, m_focus, dt));
				//pack->pack(new TaskUpdateInterface_v2(m_healthGlobe, m_focus, dt));
				//pack->pack(new TaskUpdateInterface_v3(m_manaGlobe, m_focus, dt));
				mpm->push(new TaskUpdateInterface_v0(m_gameUI, dt));
				mpm->push(new TaskUpdateInterface_v0(m_damage, dt));
				mpm->push(new TaskUpdateInterface_v1(m_exp, m_focus, dt));
				mpm->push(new TaskUpdateInterface_v2(m_healthGlobe, m_focus, dt));
				mpm->push(new TaskUpdateInterface_v3(m_manaGlobe, m_focus, dt));
				break;
			}
			}

			if (modern_Boolean_check((class Options* const)m_activeOptions.get())->option_ShowFPS)
			{
				//mpm->weak_push(new TaskUpdateInterface_v4(m_fpsText));
				//mpm->weak_push(new TaskUpdateInterface_v4(m_bmapText));
		     	//mpm->weak_push(new TaskUpdateInterface_v4(m_objectsText));
			  //  mpm->weak_push(new TaskUpdateInterface_v4(m_timersText));
				//pack->pack(new TaskUpdateInterface_v4(m_fpsText));
				//pack->pack(new TaskUpdateInterface_v4(m_bmapText));
				//pack->pack(new TaskUpdateInterface_v4(m_objectsText));
				//pack->pack(new TaskUpdateInterface_v4(m_timersText));
				//pack->pack(new TaskUpdateInterface_v4(m_heroPositionX));
				//pack->pack(new TaskUpdateInterface_v4(m_heroPositionY));
				mpm->push(new TaskUpdateInterface_v4(m_fpsText));
				mpm->push(new TaskUpdateInterface_v4(m_bmapText));
				mpm->push(new TaskUpdateInterface_v4(m_objectsText));
				mpm->push(new TaskUpdateInterface_v4(m_timersText));
				mpm->push(new TaskUpdateInterface_v4(m_heroPositionX));
				mpm->push(new TaskUpdateInterface_v4(m_heroPositionY));
			}

			//mpm->weak_push(new TaskUpdateInterface_v5(m_selectStatus, struct DirectX::XMFLOAT3(0.f, 500.f, 0.f), dt));
		//	mpm->weak_push(new TaskUpdateInterface_v0(m_selectStatusBorder, dt));

			mpm->push(new TaskUpdateInterface_v5(m_selectStatus, struct DirectX::XMFLOAT3(0.f, 500.f, 0.f), dt));
			mpm->push(new TaskUpdateInterface_v0(m_selectStatusBorder, dt));

			//mpm->push(*pack);

		//	mpm->finalize_weak_pushing();
		// 
		}
	//{
		//	class Interface* const A = (class Interface*)m_cursor.get();
		//	if (A)
		//	{
		//		modern_guard g(A);
		//		//A->SetColorFilter(1.f);
		//
		//		//A->SetOffset( XMFLOAT3(m_cameraPosition.m128_f32[0] + i2.x, m_cameraPosition.m128_f32[1] - i2.y ,0.f));
		//		A->SetPosition(m_cameraPosition);
		//		A->Update(dt);
		//	}
		//}
		//if(m_fpsText)
		//m_fpsText->Update();
		//if (m_objectsText)
		//	m_objectsText->Update();
		//const float dt = ipp::Timer::GetDeltaTime();
		//updatetime += dt;

		//if (updatetime > (1.f / 120.f))

		{
			//updatetime = 0.f;
//#pragma omp single
			m_map->Update(dt);
			mpm->barrier();
			//switch (m_editMode.load())
			//{
			//case 0:
			//{
			if (m_engine->GetGameStance() == false)
			{
				if (m_cleanupMode.load(std::memory_order::memory_order_acquire) == 1)
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
				//if (renderframe)
				{
					for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
					{
						
						m_layers[i]->Update(dt);
						
					}
				}
				
				//else
				//{
				//		{						for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
				//
				//			m_layers[i]->Update(dt);
				//		}
				//}

			}
			//mpm->barrier();

			//g_units.Sort();
			//g_units.StaticSort();
			//break;
		//}
		//case 1:
		//{
		//	m_editMode.store(0, std::memory_order::memory_order_seq_cst);
			//m_objects.Sort();
			//m_objects.QSort();

			mpm->barrier();
			//this->Sort();
			//EventManager::GetInstance()->PostSort();

//#pragma omp critical
			//Focus((class GameObject* const)m_focus.get(), ObjectFocusType::OBJECT_FOCUS_TYPE_NORMAL);

			

			for (auto&& obj : m_selectGroup)
			{
				//modern_guard g(obj);
				((Unit*)obj.get())->Select(0);
			}
			m_selectGroup.clear();



			class Agent* const agent_cursor = (class Agent* const)m_cursorAgent.get();
			if (agent_cursor)
			{
				float mousePosition[2];
				UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
				DirectX::XMFLOAT3 point = DirectX::XMFLOAT3(mousePosition[0], mousePosition[1], 0.0f);
				modern_guard g(agent_cursor);
				agent_cursor->SetVector(point);
				auto gr = this->GetUnitsInRange(agent_cursor, 80.f);
				float distanceh = INFINITY;
				class Unit* unith = nullptr;
				while (gr.size())
				{
					if (gr.top() != m_focus.get()&& gr.top()->m_flags.m_selectable == true)
					{
						//gr.top()->Select();
						modern_shared_guard g(gr.top());
						float distance = modern_xfloat3_distance2(agent_cursor->GetVector(), gr.top()->GetPosition());
						//m_selectGroup.push_back(modern_handle(gr.top()->GetHandle()));
						if (distance < distanceh)
						{
							distanceh = distance;
							unith = gr.top();
						}
					}
					gr.pop();
				}
				if(Unit::CheckIfValid(unith))
				{
					modern_guard g(unith);
					unith->Select();
					//Focus(unith, ObjectFocusType::OBJECT_FOCUS_TYPE_SELECT);
					m_selectGroup.push_back(modern_handle(unith->GetHandle()));
				}
			}
			else
			{
				assert(agent_cursor);
			}
#pragma region After Cursor Stuff
			{
				class Interface* const A = (class Interface*)m_selectStatus.get();
				class Interface* const B = (class Interface*)m_selectStatusBorder.get();
				if (A)
				{
					modern_guard g1(A);
					modern_guard g2(B);
					class Unit* const unit = (class Unit* const)GLOBAL m_lastSelectedUnit.get();
					if (unit)
					{
						A->m_flags.m_rendering = true;
						B->m_flags.m_rendering = true;
						class InterfaceStatusBarBehavior* const behaviorA = (class InterfaceStatusBarBehavior* const)A->GetBehavior();
						class Unit* const unit = (class Unit* const)GLOBAL m_lastSelectedUnit.get();
						
							modern_shared_guard g(unit);
							const float che = modern_ceil(unit->GetHealth());
							const float mhe = unit->GetMaxHealth();
							A->SetText(modern_string((int32_t)che, L".", (int32_t)mhe),30.f);
							A->PostInitializeText();
							if (behaviorA)
							{
								behaviorA->SetStatusCutXAnchorLeft(che / mhe);
							}
						
					}
					else
					{
						A->m_flags.m_rendering = false;
						B->m_flags.m_rendering = false;
					}
				}



			}
#pragma endregion
			//	break;
			//}
			//}


		}
//#pragma omp barrier
	}

	void RendererManager::Sort()
	{
		//if (m_collision)
		{
			for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
			{
				m_layers[i]->Sort();
				m_layers[i]->QSort();
			}
			MPManager::Get()->barrier();
		}
		//for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
		//{
		//	m_layers[i]->PostSort();
		//}
	}

	void RendererManager::PostSortUpdate(const float dt, const bool renderframe)
	{
		Timer::UpdatePostSort(dt);
	}

void RendererManager::Focus(GameObject* const object,const enum class ObjectFocusType type)
{
//	if (object)
//	{
//		constexpr float fadedistance = 250.f;
//		std::stack<class Tree*> stack;// = m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_OBJECT_TYPE)]->GetTreesBelow(object, fadedistance);
//		while (stack.size())
//		{
//			Tree* tree = stack.top();
//			stack.pop();
//			if (tree->m_boundingSphere.Center.y > object->m_boundingSphere.Center.y)
//			{
//				//NON-TRANSPARENT
//				tree->SetStance(0);
//				tree->SetColorFilter(1.f, 1.f, 1.f, 1.f);
//				tree->CastShadow();
//				continue;
//			}
//			else
//			{
//				//TRANSPARENT
//				
//				tree->SetColorFilter(1.1f, 1.1f, 1.1f, 0.65f);
//				tree->CastShadow(false);
//				if (tree->GetStance())
//					continue;
//				tree->SetStance(1);
//			}
//
//
//			switch (type)
//			{
//			case ObjectFocusType::OBJECT_FOCUS_TYPE_NORMAL:
//			{
//				class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
//				action->push(new ActionWaitUntil(ConditionFactory::CreateFloatCondition(
//					new FloatVariableDistanceBetweenObjects(object, tree),
//					new ConstFloatVariable(fadedistance), FloatOperatorType::FLOAT_OPERATOR_TYPE_GREATER)));
//				//action->push(new ActionWaitUntil(nullptr));
//				action->push(new ActionSetShadowCast(tree, true));
//				action->push(new ActionApplyColorFilter(tree, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f)));
//				action->push(new ActionTreeSetStance(tree, 0));
//				Timer::CreateInstantTimer(action);
//			}
//				break;
//			case ObjectFocusType::OBJECT_FOCUS_TYPE_SELECT:
//			{
//				class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
//				action->push(new ActionWaitUntil(ConditionFactory::CreateOrCondition(
//					ConditionFactory::CreateFloatCondition(new FloatVariableDistanceBetweenObjects(object, tree), new ConstFloatVariable(fadedistance), FloatOperatorType::FLOAT_OPERATOR_TYPE_GREATER),
//					ConditionFactory::CreateBooleanCondition(new BooleanVariableObjectIsSelected(object), new ConstBooleanVariable(false), BooleanOperatorType::BOOLEAN_OPERATOR_TYPE_EQUALS)
//				)));
//				action->push(new ActionSetShadowCast(tree, true));
//				action->push(new ActionApplyColorFilter(tree, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f)));
//				action->push(new ActionTreeSetStance(tree, 0));
//				Timer::CreateInstantTimer(action);
//			}
//				break;
//			}
//		}
//		
//
//
//	}
}




void RendererManager::SetInterface(const uint32 type,class Shader* shader)
{
	m_type = enum_cast<enum class UserInterfaceState>(type);
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
	class Text* const A = (class Text*)m_fpsText.get();
	if (A)
	{
		modern_guard g(A);
		A->SetText(modern_cstring("FPS ",fps).c_str());
	}
	class Text* const D = (class Text*)m_bmapText.get();
	if (D)
	{
		modern_guard g(D);
		D->SetText(modern_cstring("BMP ", GLOBAL m_mp2.size()).c_str());
	}
	class Text* const B = (class Text*)m_objectsText.get();
	if (B)
	{
		modern_guard g(B);
		B->SetText(modern_cstring("OBJ ",this->GetNumberOfObjects()).c_str());
	}
	class Text* const C = (class Text*)m_timersText.get();
	if (C)
	{
		modern_guard g(C);
		C->SetText(modern_string(L"TIM ") << modern_string(Timer::CountSleepingTimers()) << modern_string(L"...") << modern_string(Timer::CountTimers()));
	}

	class Unit* const focus = (class Unit* const)m_focus.get();
	{
		if (Unit::CheckIfValid(focus))
		{
			class Text* const E = (class Text*)m_heroPositionX.get();
			if (E)
			{
				modern_guard g(E);
				E->SetText(modern_string(L"POS X ") << modern_string((int32_t)focus->GetPosition().x));
			}

			class Text* const F = (class Text*)m_heroPositionY.get();
			if (F)
			{
				modern_guard g(F);
				F->SetText(modern_string(L"POX Y ") << modern_string((int32_t)focus->GetPosition().y));
			}
		}
		else
		{
			class Text* const E = (class Text*)m_heroPositionX.get();
			if (E)
			{
				modern_guard g(E);
				E->SetText(modern_string(L"INV"));
			}

			class Text* const F = (class Text*)m_heroPositionY.get();
			if (F)
			{
				modern_guard g(F);
				F->SetText(modern_string(L"INV"));
			}
		}
	}
	
}

void RendererManager::SetFocus(Unit* const unit)
{
	m_focus.make_handle(unit->GetHandle());
}



void RendererManager::EnableCollision(const bool collision)
{
	m_collision = collision;
}

void RendererManager::SetState(const int64_t state) modern_except_state
{
	if (m_state == state) return;

	class ActionExecuteActionArray* const marray = new ActionExecuteActionArray();

	switch (state)
	{
	case 0:
	{
		switch (m_state)
		{
		case 1:
		{
			marray->push(new ActionShowInterface(
				m_gameUI,
				modern_false
			));
			marray->push(new ActionShowInterface(
				m_exp,
				modern_false
			));
			marray->push(new ActionShowInterface(
				m_healthGlobe,
				modern_false
			));
			marray->push(new ActionShowInterface(
				m_manaGlobe,
				modern_false
			));
			break;
		}
		}
		break;
	}
	case 1:
	{
		switch (m_state)
		{
		case 0:
		{
			marray->push(new ActionShowInterface(
				m_gameUI,
				modern_true
			));
			marray->push(new ActionShowInterface(
				m_exp,
				modern_true
			));
			marray->push(new ActionShowInterface(
				m_healthGlobe,
				modern_true
			));
			marray->push(new ActionShowInterface(
				m_manaGlobe,
				modern_true
			));
			break;
		}
		}
		break;
	}
	}


	m_state = state;
	Timer::CreateInstantTimer(marray);
}

void RendererManager::Clear()
{
	for (int32_t i = 0l; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
	{
		if (m_layers[i])
		{
			m_layers[i]->Clear();
		}
	}
	this->PushAgent((class Agent*)m_cursorAgent.get());

	//test_line0.make_handle((new LineOfCollision({-1000.f,0.f}, {0.f,1000.f}))->GetHandle());
	//test_line1.make_handle((new LineOfCollision({ 0.f,1000.f }, { 1000.f,0.f }))->GetHandle());
	//test_line2.make_handle((new LineOfCollision({ -1000.f,0.f }, { 0.f,-1000.f }))->GetHandle());
	//test_line3.make_handle((new LineOfCollision({ 0.f,-1000.f }, { 1000.f,0.f }))->GetHandle());
	//test_region.make_handle((new Region({ 500.f,500.f }, { -500.f,-500.f }))->GetHandle());
}

TextFont* const RendererManager::GetFont()
{
	return m_font;
}

Interface* const RendererManager::GetHealthBarMini()
{
	return (class Interface* const)m_healthBar.get();
}

Interface* const RendererManager::GetHealthBarMiniBorder()
{
	return (class Interface* const)m_healthBarBorder.get();
}

modern_handle& RendererManager::GetCursorAgentHandle()
{
	return m_cursorAgent;
}

modern_handle& RendererManager::GetFocusAgentHandle()
{
	return m_focus;
}

std::stack<class Unit*> _vectorcall RendererManager::GetUnitsInRange(
	class Unit * const object,
	const float range)
	modern_except_state
{
	//return std::stack<Unit*>();// m_objects.GetUnitsInRange(object, range);
	return m_layers[enum_cast<int32_t>(object->GetLayerType())]->GetUnitsInRange(object, range);
}

std::stack<class Unit*> _vectorcall RendererManager::GetUnitsInRange(Agent* const agent, const float range) modern_except_state
{
	return m_layers[enum_cast<int32_t>(agent->GetLayerType())]->GetUnitsInRange(agent, range);
}

RendererManager * RendererManager::GetInstance()
{
	return m_instance;
}

size_t RendererManager::GetNumberOfObjects()
{
	size_t size = 0ull;
	for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
	{
		if (m_layers[i])
		{
			size += m_layers[i]->GetNumberOfObjects();
		}
	}
	return size;
}

__m128 RendererManager::GetNumberOfObjectsX4()
{
//	return m_objects.GetSizeX4();
	return __m128();
}

std::vector<int64> RendererManager::GetNumberOfObjectsVector()
{
//	return m_objects.GetSizeVector();
	return std::vector<int64>();
}




