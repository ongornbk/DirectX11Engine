#include "ResourceManager.h"
#include "LUAManager.h"
#include "Camera.h"
#include "SettingsC.h"
#include "Engine.h"
#include "Global.h"
#include "GameScene.h"
#include "IPP.h"
#include "Network.h"

#ifdef __cplusplus
extern "C"
#endif // __cplusplus
{


namespace lua_callback
{
#pragma region
	using std::string;
	using std::wstring;
#pragma endregion

#define LUA_STRING lua_tostring
#define LUA_FLOAT (float)lua_tointeger
#define LUA_BOOLEAN lua_toboolean

	static void SetResourceManager(ResourceManager* manager);
	static void SetCamera(Camera* camera);
	static void Initialize(Engine* engine);
	static void SetInput(Input* input);
	static void SetRendererManager(RendererManager* renderer);

	namespace
	{

		static ResourceManager*     m_resources;
		static Camera*              m_camera;
		static Engine*              m_engine;
		static Input*               m_input;
		static Global*              m_global;
		static ID3D11Device*        m_device;
		static ID3D11DeviceContext* m_deviceContext;
		static TextureShader*       m_shader;
		static RendererManager*     m_renderer;

	}

	static void SetRendererManager(RendererManager* manager)
	{
		m_renderer = manager;
	}

	static void SetResourceManager(ResourceManager* manager)
	{
		m_resources = manager;
	}

	static void SetCamera(Camera* camera)
	{
		m_camera = camera;
	}

	static void InitializeGraphics()
	{
		m_device = m_engine->GetGraphics()->GetDevice();
		m_deviceContext = m_engine->GetGraphics()->GetDeviceContext();
		m_shader = (TextureShader*)m_resources->GetShaderByName("texture.fx");
	}

	static void Initialize(Engine* engine)
	{
		m_engine = engine;
		m_global = Global::GetInstance();

	}

	static void SetInput(Input* input)
	{
		m_input = input;
	}

	static int LoadTexture(lua_State* state)
	{
#pragma warning(disable : 4996)
			string str = LUA_STRING(state,1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string,ws.c_str());
			m_resources->LoadTextureResource(wide_string);
			delete wide_string;
		return 0;
	}

	static int LoadSound(lua_State* state)
	{
#pragma warning(disable : 4996)
		string str = LUA_STRING(state, 1);
		
		wchar_t* wide_string = new wchar_t[str.length() + 1];
		wstring ws = std::wstring(str.begin(), str.end()).c_str();
		wcscpy(wide_string, ws.c_str());
		m_resources->LoadSoundResource(wide_string);
		delete wide_string;
		return 0;
	}


	static int InitializeProjectionMatrix(lua_State* state)
	{
		m_camera->InitializeProjectionMatrix((float)XM_PI / LUA_FLOAT(state, 1), Settings::GetAspectRatio(),1.0f / LUA_FLOAT(state, 2), LUA_FLOAT(state, 3));
		return 0;
	}

	static int InitializeOrthoMatrix(lua_State* state)
	{
		m_camera->InitializeOrthoMatrix(*(Settings::get()->RESOLUTION_X), *(Settings::get()->RESOLUTION_Y), 1.0f / LUA_FLOAT(state, 1), LUA_FLOAT(state, 2));
		return 0;
	}

	static int SetCameraPosition(lua_State* state)
	{
		XMVECTOR position;
		position.m128_f32[0] = LUA_FLOAT(state, 1);
		position.m128_f32[1] = LUA_FLOAT(state, 2);
		position.m128_f32[2] = LUA_FLOAT(state, 3);
		m_camera->SetPosition(position);
		return 0;
	}

	static int AddMusic(lua_State* state)
	{
		string str = LUA_STRING(state, 1);
		m_engine->AddMusicSound(str, LUA_FLOAT(state, 2), LUA_BOOLEAN(state, 3));
		return 0;
	}

	static int AddModelPaths(lua_State* state)
	{
		string str = LUA_STRING(state, 1);
		m_engine->AddModelPaths(str);
		return 0;
	}

	static int32_t PlayMusic(lua_State* state) noexcept
	{
#pragma warning(disable : 4996)
		string str = LUA_STRING(state, 1);

		wchar_t* wide_string = new wchar_t[str.length() + 1];
		wstring ws = std::wstring(str.begin(), str.end()).c_str();
		wcscpy(wide_string, ws.c_str());
		m_engine->PlayMusic(wide_string);
		delete wide_string;
		return 0;
	}

	static int32_t StartServer(lua_State* state) noexcept
	{
		Network::StartServer((uint16_t)lua_tointeger(state, 1));
		return 0;
	}

	static int32_t __PostQuitMessage(lua_State* state) noexcept
	{
		PostQuitMessage((int)lua_tointeger(state, 1));
		return 0;
	}

	static int32_t __IsKeyHit(lua_State* state) noexcept
	{
		if (m_input->IsKeyHit((unsigned int)lua_tointeger(state,1)))
		{
			lua_pushboolean(state, true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}
	static int32_t __IsKeyPressed(lua_State* state) noexcept
	{
		if (m_input->IsKeyDown((uint32_t)lua_tointeger(state, 1)))
		{
			lua_pushboolean(state, true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}

	static int32_t __GetMouseState(lua_State* state) noexcept
	{
		if (m_input->GetMouseState((uint32_t)lua_tointeger(state, 1)))
		{
			lua_pushboolean(state,true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}

	static int32_t __GetMousePressed(lua_State* state) noexcept
	{
		lua_pushboolean(state,m_input->GetMousePressed((int32_t)lua_tointeger(state,1)));
		return 1;
	}

	static int CreateUnit(lua_State* state) noexcept
	{
		Unit* unit = new Unit();
		m_global->m_lastCreatedUnit = unit;
		return 0;
	}

	static int CreateDoodads(lua_State* state) noexcept
	{
		Doodads* doodads = new Doodads();
		m_global->m_lastCreatedDoodads = doodads;
		return 0;
	}

	static int32_t GetMousePosition(lua_State* state) noexcept
	{
		int16_t xm, ym;
		UserInterface::GetMousePosition(xm, ym);
		m_global->m_lastPoint = XMFLOAT3((float)xm,(float)ym, 0.0f);
		lua_pushinteger(state, (int32_t)xm);
		lua_pushinteger(state, (int32_t)ym);
		return 2;
	}

	static int32_t PickLastSelectedUnit(lua_State*) noexcept
	{
		Unit* unit = m_global->m_lastSelectedUnit;
		if (unit)
		{
			m_global->m_lastPickedUnit = unit;
		}
		return 0;
	}

	static int32_t PickLastCreatedUnit(lua_State*) noexcept
	{
		Unit* unit = m_global->m_lastCreatedUnit;
		if (unit)
		{
			m_global->m_lastPickedUnit = unit;
		}
		return 0;
	}

	static int32_t GiveTaskGotoPoint(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			Task* task = new Task();
			TaskGotoPoint* tgtp = new TaskGotoPoint();
			tgtp->destination.x = LUA_FLOAT(state, 1);
			tgtp->destination.y = LUA_FLOAT(state, 2);
			tgtp->object = unit;
			task->m_content.taskGotoPoint = tgtp;
			task->m_type = Task::Type::TASKGOTOPOINT;
			unit->GiveTask(task);
		}
			return 0;
	}

	static int32_t SetTaskGotoPoint(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			Task* task = new Task();
			TaskGotoPoint* tgtp = new TaskGotoPoint();
			tgtp->destination = m_global->m_lastPoint;
			tgtp->object = unit;
			task->m_content.taskGotoPoint = tgtp;
			task->m_type = Task::Type::TASKGOTOPOINT;
			unit->SetTask(task);
		}
		return 0;
	}

	static int32_t CleanTasks(lua_State* state) noexcept
	{

		m_global->m_lastPickedUnit->DiscardTasks();
		return 0;
	}

	static int32_t LockCameraOnUnit(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			m_engine->GetCameraControl()->LockCameraPositionOnUnit(unit);
		}
		return 0;
	}

	static int32_t InitializeUnit(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
		string str = lua_tostring(state, 1);
		float size = (float)lua_tointeger(state, 2);
		float collision = (float)lua_tointeger(state, 3);
		float p_x = (float)lua_tointeger(state, 4);
		float p_y = (float)lua_tointeger(state, 5);
		float p_z = (float)lua_tointeger(state, 6);
		bool wander = lua_toboolean(state, 7);
		XMFLOAT3 pos(p_x, p_y, p_z);
		wchar_t* wide_string = new wchar_t[str.length() + 1];
		wstring ws = std::wstring(str.begin(), str.end()).c_str();
		wcscpy(wide_string, ws.c_str());


			unit->Initialize(m_device, m_deviceContext, m_shader, wide_string, size, collision, pos, wander);
			m_renderer->PushUnit(unit);
		}
		return 0;
		
	}

	static int32_t InitializeDoodads(lua_State* state) noexcept
	{
		Doodads* doodads = m_global->m_lastCreatedDoodads;
		if (doodads)
		{
			string str = lua_tostring(state, 1);
			float size = (float)lua_tointeger(state, 2);
			float collision = (float)lua_tointeger(state, 3);
			float p_x = (float)lua_tointeger(state, 4);
			float p_y = (float)lua_tointeger(state, 5);
			float p_z = (float)lua_tointeger(state, 6);
			bool pushable = lua_toboolean(state, 7);
			XMFLOAT3 pos(p_x, p_y, p_z);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());


			doodads->Initialize(m_device, m_deviceContext, m_shader, wide_string, size, collision, pos, pushable);
			m_renderer->PushDoodads(doodads);
		}
		return 0;

	}

	static int32_t SetWalkingStance(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
			Unit::WalkingStance ws;
			switch (lua_tointeger(state, 1))
			{
			case 0:
				ws = Unit::WalkingStance::WALK;
				break;
			case 1:
				ws = Unit::WalkingStance::RUN;
				break;
			}
			unit->SetWalkingStance(ws);
		return 0;
	}

	static int32_t ChangeWalkingStance(lua_State* state) noexcept
	{
		m_global->m_lastPickedUnit->ChangeWalkingStance();
		return 0;
	}

	static int32_t SetUnitSpeed(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->SetSpeed((float)lua_tointeger(state,1));
		}
		return 0;
	}

	static int32_t PushUnitVariable(lua_State* state) noexcept
	{
		std::string name = LUA_STRING(state, 1);
		bool result = m_global->m_variables.PushUnit(name, m_global->m_lastPickedUnit);
		lua_pushboolean(state, result);
		return 1;
	}

	static int EraseUnitVariable(lua_State* state)
	{
		std::string name = LUA_STRING(state, 1);
		bool result = m_global->m_variables.EraseUnit(name);
		lua_pushboolean(state, result);
		return 1;
	}

	static int GetUnitVariable(lua_State* state)
	{
		std::string name = LUA_STRING(state, 1);
		Unit* unit = m_global->m_variables.GetUnit(name);
		if (unit)
		{
			m_global->m_lastPickedUnit = unit;
			lua_pushboolean(state, true);
		}
		else
		lua_pushboolean(state, false);
		return 1;
	}

	static int SetUnitPosition(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->SetPosition(XMFLOAT3((float)lua_tointeger(state, 1), (float)lua_tointeger(state, 2), (float)lua_tointeger(state, 3)));
		}
		return 0;
	}
	
	static int GetUnitPosition(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			XMFLOAT3 position;
			position = unit->Center;
			lua_pushinteger(state,(int)position.x);
			lua_pushinteger(state,(int)position.y);
			return 2;
		}
		return 0;
	}

	static int GetUnitsInRange(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		float range = LUA_FLOAT(state, 1);
		if (unit)
		{
			m_global->m_stack = UnitsVector::GetUnitsInRange(unit, range);
			m_global->m_size = (uint32_t)m_global->m_stack.size();
			return 0;
		}
		return 0;
	}

	static int PopGroup(lua_State* state)
	{
		
		if (m_global->m_stack.empty())
		{
			lua_pushboolean(state, false);
		}
		else
		{
			m_global->m_lastPickedUnit = m_global->m_stack.top();
			m_global->m_stack.pop();
			lua_pushboolean(state, true);
		}
		return 1;
	}

	static int GetSize(lua_State* state)
	{
		lua_pushinteger(state, (int)m_global->m_size);
		return 1;
	}

	static int SetUnitRotations(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->SetRotations((float)lua_tointeger(state, 1));
		}
		return 0;
	}

	static int SetRenderingStyle(lua_State* state)
	{
		RendererManager::RenderingStyle rs;
		switch (lua_tointeger(state, 1))
		{
		case 0:
			rs = RendererManager::RenderingStyle::REVERSE;
			break;
		case 1:
			rs = RendererManager::RenderingStyle::NOREVERSE;
			break;
		}
		m_renderer->SetRenderingStyle(rs);
		return 0;
	}

	static int SetInterface(lua_State* state)
	{
		m_renderer->SetInterface((unsigned int)lua_tointeger(state,1), m_resources->GetShaderByName("texture.fx"));
		return 0;
	}

	static int PauseGame(lua_State* state)
	{
		m_engine->PauseGame();
		return 0;
	}

	static int ResumeGame(lua_State* state)
	{
		m_engine->ResumeGame();
		return 0;
	}

	static int LoadFont(lua_State* state) //EXPORTED
	{
		m_engine->AddFont(lua_tostring(state, 1), LUA_FLOAT(state, 2), LUA_FLOAT(state, 3));
		return 0;
	}

	static int32_t SetTilesMultiplier(lua_State* state) noexcept
	{
		SetCellMultiplier(LUA_FLOAT(state, 1));
		return 0;
	}

	static int32_t __LoadTilesResourceFromFile(lua_State* state)
	{
		LoadTilesResourceFromFile(lua_tostring(state, 1));
		return 0;
	}

	static int SetTile(lua_State* state) //EXPORTED
	{
		XMFLOAT2 position;
		position.x= m_global->m_lastPoint.x;
		position.y = m_global->m_lastPoint.y;
		m_renderer->SetTile(position, (int32_t)lua_tointeger(state, 1));
		return 0;
	}

	static int SaveInstance(lua_State* state)
	{
		m_renderer->SaveInstanceToFile(lua_tostring(state, 1));
		return 0;
	}

	static int LoadInstance(lua_State* state)
	{
		m_renderer->LoadInstanceToFile(lua_tostring(state, 1));
		return 0;
	}

	static int GetInput(lua_State* state)
	{
		lua_pushstring(state, (ipp::Console::GetInput().c_str()));
		return 1;
	}

	static int Println(lua_State* state)
	{
		ipp::Console::Println(lua_tostring(state, 1));
		return 0;
	}

	static void RegisterFunctions()
	{
		lua_State* m_lua = lua::GetInstance();

		//ResourceManager
		lua_register(m_lua, "LoadTexture", lua_callback::LoadTexture);
		lua_register(m_lua, "LoadSound", lua_callback::LoadSound);
		//Camera
		lua_register(m_lua, "InitializeProjectionMatrix", lua_callback::InitializeProjectionMatrix);
		lua_register(m_lua, "InitializeOrthoMatrix", lua_callback::InitializeOrthoMatrix);
		lua_register(m_lua, "SetCameraPosition", lua_callback::SetCameraPosition);
		lua_register(m_lua, "LockCameraOnUnit", lua_callback::LockCameraOnUnit);
		//Music
		lua_register(m_lua, "AddMusic", lua_callback::AddMusic);
		lua_register(m_lua, "PlayMusic", lua_callback::PlayMusic);
		//System
		lua_register(m_lua, "PostQuitMessage", lua_callback::__PostQuitMessage);
		lua_register(m_lua, "SaveInstance", lua_callback::SaveInstance);
		lua_register(m_lua, "LoadInstance", lua_callback::LoadInstance);
		//Input
		lua_register(m_lua, "IsKeyHit", lua_callback::__IsKeyHit);
		lua_register(m_lua, "IsKeyPressed", lua_callback::__IsKeyPressed);
		lua_register(m_lua, "GetMouseState", lua_callback::__GetMouseState);
		lua_register(m_lua, "GetMousePressed", lua_callback::__GetMousePressed);
		lua_register(m_lua, "GetMousePosition", lua_callback::GetMousePosition);
		//Units
		lua_register(m_lua,"CreateUnit", lua_callback::CreateUnit);
		lua_register(m_lua,"InitializeUnit", lua_callback::InitializeUnit);
		lua_register(m_lua,"SetWalkingStance", lua_callback::SetWalkingStance);
		lua_register(m_lua,"ChangeWalkingStance", lua_callback::ChangeWalkingStance);
		lua_register(m_lua,"SetUnitSpeed", lua_callback::SetUnitSpeed);
		lua_register(m_lua,"SetUnitRotations", lua_callback::SetUnitRotations);
		//Doodads
		lua_register(m_lua, "CreateDoodads", lua_callback::CreateDoodads);
		lua_register(m_lua, "InitializeDoodads", lua_callback::InitializeDoodads);
		//lua_register(m_lua,"PickHero", lua_callback::PickHero);
		lua_register(m_lua, "PickLastCreatedUnit", lua_callback::PickLastCreatedUnit);
		lua_register(m_lua, "PickLastSelectedUnit", lua_callback::PickLastSelectedUnit);
		lua_register(m_lua,"GiveTaskGotoPoint", lua_callback::GiveTaskGotoPoint);
		lua_register(m_lua,"SetTaskGotoPoint", lua_callback::SetTaskGotoPoint);
		lua_register(m_lua,"CleanTasks", lua_callback::CleanTasks);
		lua_register(m_lua,"GetUnitPosition", lua_callback::GetUnitPosition);
		lua_register(m_lua,"AddModelPaths", lua_callback::AddModelPaths);
		lua_register(m_lua, "SetUnitPosition", lua_callback::SetUnitPosition);
		lua_register(m_lua, "GetUnitsInRange", lua_callback::GetUnitsInRange);
		lua_register(m_lua, "GetSize", lua_callback::GetSize);
		lua_register(m_lua, "PopGroup", lua_callback::PopGroup);
		lua_register(m_lua, "GetUnitPosition", lua_callback::GetUnitPosition);
		lua_register(m_lua, "PushUnitVariable", lua_callback::PushUnitVariable);
		lua_register(m_lua, "GetUnitVariable", lua_callback::GetUnitVariable);
		lua_register(m_lua, "EraseUnitVariable", lua_callback::EraseUnitVariable);
		//RendererManager
		lua_register(m_lua,"SetRendereringStyle", lua_callback::SetRenderingStyle);
		lua_register(m_lua,"SetInterface", lua_callback::SetInterface);
		//Engine
		lua_register(m_lua,"ResumeGame", lua_callback::ResumeGame);
		lua_register(m_lua,"PauseGame", lua_callback::PauseGame);
		//Fonts
		lua_register(m_lua, "LoadFont", lua_callback::LoadFont);
		//Tiles
		lua_register(m_lua, "SetTilesMultiplier", lua_callback::SetTilesMultiplier);
		lua_register(m_lua, "SetTile", lua_callback::SetTile);
		lua_register(m_lua, "LoadTilesResourceFromFile", lua_callback::__LoadTilesResourceFromFile);
		//Console
		lua_register(m_lua, "GetInput", lua_callback::GetInput);
		lua_register(m_lua, "Println", lua_callback::Println);
		//Network
		lua_register(m_lua, "StartServer", lua_callback::StartServer);
	}

}

}
