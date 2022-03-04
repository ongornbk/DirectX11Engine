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
#include "ConditionFactory.h"
#include "modern/modern_cstring.h"
#include "Options.h"
#include "ActionSetTextAlignment.h"
#include "ActionInitializeInterface.h"
#include "ActionSetInterfaceOffset.h"

#include <future>
#include <mutex>
#include <stack>

//TEMP
//#include <d2d1.h>
//#include <dwrite.h>

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

RendererManager::RendererManager(
	class Engine* const engine,
	class Shader* const units,
	class Shader* const ui,
	class Shader* const shadow,
	class Shader* const select,
	class Shader* const inter
) :
	m_engine(engine),
	m_unitsShader(units),
	m_shader(ui),
	m_shadowShader(shadow),
	m_selectShader(select),
	m_interfaceShader(inter),
	m_focus(nullptr),
	m_collision(false),
	//m_fpsText(nullptr),
	//m_objectsText(nullptr),
	m_fps(0)
{

	m_instance = this;
	new Options();
	m_activeOptions.make_handle(Options::GetInstance());


	
	Tile::SetGlobals(Engine::GetEngine()->GetGraphics()->GetDevice(), GETSHADER "tile.fx" CLOSE,this);
	m_map = new TileMap(1.0f,1.0f,0.2f,true);
	m_map->Initialize();
	TileMap::SetCurrentTileMap(m_map);
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
	m_font->Initialize(engine->GetGraphics()->GetDevice(), engine->GetGraphics()->GetDeviceContext(),m_interfaceShader);

	class Agent* const agent_cursor = new class Agent();
	agent_cursor->Initialize(struct DirectX::XMFLOAT3(0.f, 0.f, 0.f));
	m_cursorAgent.make_handle(agent_cursor->GetHandle());

	


	class ActionExecuteActionArray* const marray = new ActionExecuteActionArray();

	marray->push(new ActionInitializeText(
		m_fpsText,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_font, 20.f
	));

	marray->push(new ActionSetTextAlignment(m_fpsText,TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_fpsText,
		struct DirectX::XMFLOAT3(-935.f, 490.f, 0.f
		)));

	marray->push(new ActionInitializeText(
		m_objectsText,
		engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		m_font, 20.f
	));

	marray->push(new ActionSetTextAlignment(m_objectsText, TextAlignment::TEXT_ALIGN_LEFT));

	marray->push(new ActionTranslateText(
		m_objectsText,
		struct DirectX::XMFLOAT3(-935.f, 520.f, 0.f
		)));

	marray->push(new ActionInitializeInterface(
		m_selectStatus, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		class  modern_string(L"health_bar"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(160.f, 60.f)
	));

	marray->push(new ActionSetInterfaceOffset(
		m_selectStatus,
		struct DirectX::XMFLOAT3(0.f,480.f,0.f)
	));

	marray->push(new ActionInitializeInterface(
		m_selectStatusBorder, engine->GetGraphics()->GetDevice(),
		engine->GetGraphics()->GetDeviceContext(),
		m_interfaceShader,
		class  modern_string(L"health_bar_border"),
		struct DirectX::XMFLOAT3(0.f, 0.f, 0.f),
		struct DirectX::XMFLOAT2(160.f, 60.f)
	));

	marray->push(new ActionSetInterfaceOffset(
		m_selectStatusBorder,
		struct DirectX::XMFLOAT3(0.f, 480.f, 0.f)
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

void RendererManager::Push(class EObject* const object, const enum class RenderLayerType layer)
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
		struct ID3D11Device* const device = Engine::GetEngine()->GetGraphics()->GetDevice();
		struct ShaderPackage pck(deviceContext,m_unitsShader,m_shadowShader,m_selectShader,m_interfaceShader);

		GRAPHICS EnableAlphaBlending(true);


			m_map->Render(deviceContext, viewMatrix, projectionMatrix, m_cameraPosition);


			for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
			{
				m_layers[i]->Render(deviceContext, viewMatrix, projectionMatrix, pck);
			}



			pck.BeginInterface();
			GRAPHICS EnableAlphaBlending(true);

			m_ui->Render(deviceContext, viewMatrix, projectionMatrix);

			if (((Options*)m_activeOptions.get())->option_ShowFPS)
			{
				class Text* const A = (class Text*)m_fpsText.get();
				if (A)
				{
					modern_guard g(A);
					A->PreRender(deviceContext, viewMatrix, projectionMatrix, pck.BeginShadow());
					A->Render(deviceContext, viewMatrix, projectionMatrix, pck.BeginInterface());

				}
				class Text* const B = (class Text*)m_objectsText.get();
				if (B)
				{
					modern_guard g(B);
					B->PreRender(deviceContext, viewMatrix, projectionMatrix, pck.BeginShadow());
					B->Render(deviceContext, viewMatrix, projectionMatrix, pck.BeginInterface());
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
					A->SetColorFilter(0.f, 0.f, 0.f, 0.3f);
					A->Render(deviceContext, viewMatrix, projectionMatrix, pck);
					//A->SetColorFilter(1.f);
					//A->Render(deviceContext, viewMatrix, projectionMatrix, pck);
				}
			}
			{
				class Interface* const A = (class Interface*)m_selectStatusBorder.get();
				if (A)
				{
					modern_guard g(A);
					A->SetColorFilter(1.f);
					A->Render(deviceContext, viewMatrix, projectionMatrix, pck);
				}
			}

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
		
	
}

	//static float updatetime = 0.f;

	void RendererManager::Update(const float dt,const bool renderframe)
	{

		GLOBAL m_selectStatus = false;

		m_cameraPosition = CAMERA GetPosition();
		m_ui->Update(m_cameraPosition);

		if (((Options*)m_activeOptions.get())->option_ShowFPS)
		{
			class Text* const A = (class Text*)m_fpsText.get();
			if (A)
			{
				modern_guard g(A);
				A->SetPosition(m_cameraPosition);
				A->Update();

			}
			class Text* const B = (class Text*)m_objectsText.get();
			if (B)
			{
				modern_guard g(B);
				B->SetPosition(m_cameraPosition);
				B->Update();
			}
		}
		{
			class Interface* const A = (class Interface*)m_selectStatus.get();
			if (A)
			{
				modern_guard g(A);
				//A->PreRender(deviceContext, viewMatrix, projectionMatrix, pck.BeginShadow());
				//A->Render(deviceContext, viewMatrix, projectionMatrix, pck.BeginInterface());
				A->SetPosition(m_cameraPosition);
				A->Update(dt);
				
			}
		} {
			class Interface* const A = (class Interface*)m_selectStatusBorder.get();
			if (A)
			{
				modern_guard g(A);
				//A->PreRender(deviceContext, viewMatrix, projectionMatrix, pck.BeginShadow());
				//A->Render(deviceContext, viewMatrix, projectionMatrix, pck.BeginInterface());
				A->SetPosition(m_cameraPosition);
				A->Update(dt);
			}
		}
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
				if (renderframe)
				{
					for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
					{
						
						m_layers[i]->Update(dt);
					}
				}
				else
				{
						{						for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)

							m_layers[i]->Update(dt);
						}
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

			if (m_collision)
			{
				for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
				{
					m_layers[i]->Sort();
					m_layers[i]->QSort();
				}

			}

//#pragma omp critical
			Focus(m_focus, ObjectFocusType::OBJECT_FOCUS_TYPE_NORMAL);

			

			for (auto obj : m_selectGroup)
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
				auto gr = this->GetUnitsInRange(agent_cursor, 90.f);
				while (gr.size())
				{
					if (gr.top() != m_focus)
					{
						gr.top()->Select();
						m_selectGroup.push_back(modern_handle(gr.top()->GetHandle()));
					}
					gr.pop();
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
					if (GLOBAL m_selectStatus)
					{
						A->m_flags.m_rendering = true;
						B->m_flags.m_rendering = true;

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

void RendererManager::Focus(EObject* const object,const enum class ObjectFocusType type)
{
	if (object)
	{
		constexpr float fadedistance = 250.f;
		std::stack<class Tree*> stack = m_layers[enum_cast<int32_t>(RenderLayerType::ENUM_OBJECT_TYPE)]->GetTreesBelow(object, fadedistance);
		while (stack.size())
		{
			Tree* tree = stack.top();
			stack.pop();
			if (tree->m_boundingSphere.Center.y > object->m_boundingSphere.Center.y)
			{
				//NON-TRANSPARENT
				tree->SetColorFilter(1.f, 1.f, 1.f, 1.f);
				tree->CastShadow();
				continue;
			}
			else
			{
				//TRANSPARENT
				tree->SetColorFilter(1.1f, 1.1f, 1.1f, 0.65f);
				tree->CastShadow(false);
			}
			switch (type)
			{
			case ObjectFocusType::OBJECT_FOCUS_TYPE_NORMAL:
			{
				class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
				action->push(new ActionWaitUntil(ConditionFactory::CreateFloatCondition(new FloatVariableDistanceBetweenObjects(object, tree), new ConstFloatVariable(fadedistance), FloatOperatorType::FLOAT_OPERATOR_TYPE_GREATER)));
				action->push(new ActionSetShadowCast(tree, true));
				action->push(new ActionApplyColorFilter(tree, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f)));
				Timer::CreateInstantTimer(action);
			}
				break;
			case ObjectFocusType::OBJECT_FOCUS_TYPE_SELECT:
			{
				class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
				action->push(new ActionWaitUntil(ConditionFactory::CreateOrCondition(
					ConditionFactory::CreateFloatCondition(new FloatVariableDistanceBetweenObjects(object, tree), new ConstFloatVariable(fadedistance), FloatOperatorType::FLOAT_OPERATOR_TYPE_GREATER),
					ConditionFactory::CreateBooleanCondition(new BooleanVariableObjectIsSelected(object), new ConstBooleanVariable(false), BooleanOperatorType::BOOLEAN_OPERATOR_TYPE_EQUALS)
				)));
				action->push(new ActionSetShadowCast(tree, true));
				action->push(new ActionApplyColorFilter(tree, DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f)));
				Timer::CreateInstantTimer(action);
			}
				break;
			}
		}
		


	}
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
	class Text* const A = (class Text*)m_fpsText.get();
	if (A)
	{
		modern_guard g(A);
			A->SetText(modern_cstring("FPS ",fps).c_str());

	}
	class Text* const B = (class Text*)m_objectsText.get();
	if (B)
	{
		modern_guard g(B);
		B->SetText(modern_cstring("OBJ ",this->GetNumberOfObjects()).c_str());
	}
	//if(m_fpsText)
	//m_fpsText->SetText(modern_cstring(fps).c_str());
	//if (m_objectsText)
	//	m_objectsText->SetText(modern_cstring(this->GetNumberOfObjects()).c_str());
}

void RendererManager::SetFocus(Unit* const unit)
{
	m_focus = unit;
}



void RendererManager::EnableCollision(const bool collision)
{
	m_collision = collision;
}

void RendererManager::Clear()
{
	for (int32_t i = 0; i < enum_cast<int32_t>(RenderLayerType::COUNT); i++)
	{
		if (m_layers[i])
		{
			m_layers[i]->Clear();
		}
	}
	this->PushAgent((class Agent*)m_cursorAgent.get());
}

TextFont* const RendererManager::GetFont()
{
	return m_font;
}

std::stack<class Unit*> _vectorcall RendererManager::GetUnitsInRange(
	class Unit * const object,
	const float range)
	noexcept
{
	//return std::stack<Unit*>();// m_objects.GetUnitsInRange(object, range);
	return m_layers[enum_cast<int32_t>(object->GetLayerType())]->GetUnitsInRange(object, range);
}

std::stack<class Unit*> _vectorcall RendererManager::GetUnitsInRange(Agent* const agent, const float range) noexcept
{
	return m_layers[enum_cast<int32_t>(agent->GetLayerType())]->GetUnitsInRange(agent, range);
}

RendererManager * RendererManager::GetInstance()
{
	return m_instance;
}

size_t RendererManager::GetNumberOfObjects()
{
	size_t size = 0u;
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
}

std::vector<int64> RendererManager::GetNumberOfObjectsVector()
{
//	return m_objects.GetSizeVector();
	return std::vector<int64>();
}




