#include "ResourceManager.h"
#include "LUAManager.h"
#include "Camera.h"
#include "SettingsC.h"
#include "Engine.h"
#include "Global.h"
#include "GameScene.h"

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

	static int LoadTexture(lua_State* state) //EXPORTED
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

	static int LoadSound(lua_State* state) //EXPORTED
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


	static int InitializeProjectionMatrix(lua_State* state) //EXPORTED
	{
		m_camera->InitializeProjectionMatrix((float)XM_PI / LUA_FLOAT(state, 1), Settings::GetAspectRatio(),1.0f / LUA_FLOAT(state, 2), LUA_FLOAT(state, 3));
		return 0;
	}

	static int InitializeOrthoMatrix(lua_State* state) //EXPORTED
	{
		m_camera->InitializeOrthoMatrix(*(Settings::get()->RESOLUTION_X), *(Settings::get()->RESOLUTION_Y), 1.0f / LUA_FLOAT(state, 1), LUA_FLOAT(state, 2));
		return 0;
	}

	static int SetCameraPosition(lua_State* state) //EXPORTED
	{
		XMVECTOR position;
		position.m128_f32[0] = LUA_FLOAT(state, 1);
		position.m128_f32[1] = LUA_FLOAT(state, 2);
		position.m128_f32[2] = LUA_FLOAT(state, 3);
		m_camera->SetPosition(position);
		return 0;
	}

	static int AddMusic(lua_State* state) //EXPORTED
	{
		string str = LUA_STRING(state, 1);
		m_engine->AddMusicSound(str, LUA_FLOAT(state, 2), LUA_BOOLEAN(state, 3));
		return 0;
	}

	static int AddModelPaths(lua_State* state) //EXPORTED
	{
		string str = LUA_STRING(state, 1);
		m_engine->AddModelPaths(str);
		return 0;
	}

	static int PlayMusic(lua_State* state) //EXPORTED
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

	static int __PostQuitMessage(lua_State* state) //EXPORTED
	{
		PostQuitMessage((int)lua_tointeger(state,1));
		return 0;
	}

	static int __IsKeyHit(lua_State* state) //EXPORTED
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

	static int __GetMouseState(lua_State* state) //EXPORTED
	{
		if (m_input->GetMouseState((unsigned int)lua_tointeger(state, 1)))
		{
			lua_pushboolean(state,true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}

	static int CreateUnit(lua_State* state)
	{
		Unit* unit = new Unit();
		m_global->m_lastCreatedUnit = unit;
		return 0;
	}

	static int GetMousePosition(lua_State* state)
	{
		int xm, ym;
		UserInterfaceGame::GetMousePosition(xm, ym);
		m_global->m_lastPoint = XMFLOAT3((float)xm, (float)ym, 0.0f);
		lua_pushinteger(state, xm);
		lua_pushinteger(state, ym);
		return 2;
	}

	static int GetHero(lua_State*)
	{
		m_global->m_lastCreatedUnit = GameScene::GetHero();
		return 0;
	}

	static int GiveTaskGotoPoint(lua_State* state)
	{
			Task* task = new Task();
			TaskGotoPoint* tgtp = new TaskGotoPoint();
			tgtp->destination = m_global->m_lastPoint;
			tgtp->object = m_global->m_lastCreatedUnit;
			task->m_content.taskGotoPoint = tgtp;
			task->m_type = Task::Type::TASKGOTOPOINT;
			m_global->m_lastCreatedUnit->GiveTask(task);
			return 0;
	}

	static int SetTaskGotoPoint(lua_State* state)
	{
		Task* task = new Task();
		TaskGotoPoint* tgtp = new TaskGotoPoint();
		tgtp->destination = m_global->m_lastPoint;
		tgtp->object = m_global->m_lastCreatedUnit;
		task->m_content.taskGotoPoint = tgtp;
		task->m_type = Task::Type::TASKGOTOPOINT;
		m_global->m_lastCreatedUnit->SetTask(task);
		return 0;
	}

	static int CleanTasks(lua_State* state)
	{

		m_global->m_lastCreatedUnit->DiscardTasks();
		return 0;
	}

	static int LockCameraOnUnit(lua_State* state)
	{
		m_engine->GetCameraControl()->LockCameraPositionOnUnit(m_global->m_lastCreatedUnit);
		return 0;
	}

	static int InitializeUnit(lua_State* state)
	{
		Unit* unit = m_global->m_lastCreatedUnit;
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

	static int SetWalkingStance(lua_State* state)
	{
		Unit* unit = m_global->m_lastCreatedUnit;
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

	static int ChangeWalkingStance(lua_State* state)
	{
		m_global->m_lastCreatedUnit->ChangeWalkingStance();
		return 0;
	}

	static int SetUnitSpeed(lua_State* state)
	{
		Unit* unit = m_global->m_lastCreatedUnit;
		if (unit)
		{
			unit->SetSpeed((float)lua_tointeger(state,1));
		}
		return 0;
	}
	
	static int GetUnitPosition(lua_State* state)
	{
		Unit* unit = m_global->m_lastCreatedUnit;
		if (unit)
		{
			XMFLOAT3 position;
			position = unit->GetPosition();
			lua_pushinteger(state,(int)position.x);
			lua_pushinteger(state,(int)position.y);
			return 2;
		}
		return 0;
	}

	static int SetUnitRotations(lua_State* state)
	{
		Unit* unit = m_global->m_lastCreatedUnit;
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

	static void RegisterFunctions()
	{

		lua_State* m_lua = lua::GetInstance();

		//ResourceManager
		lua_register(m_lua, "LoadTexture", LoadTexture);
		lua_register(m_lua, "LoadSound", LoadSound);
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
		//Input
		lua_register(m_lua, "IsKeyHit", lua_callback::__IsKeyHit);
		lua_register(m_lua, "GetMouseState", lua_callback::__GetMouseState);
		lua_register(m_lua, "GetMousePosition", GetMousePosition);
		//Units
		lua_register(m_lua, "CreateUnit", lua_callback::CreateUnit);
		lua_register(m_lua, "InitializeUnit", lua_callback::InitializeUnit);
		lua_register(m_lua, "SetWalkingStance", lua_callback::SetWalkingStance);
		lua_register(m_lua, "ChangeWalkingStance",lua_callback::ChangeWalkingStance);
		lua_register(m_lua, "SetUnitSpeed", lua_callback::SetUnitSpeed);
		lua_register(m_lua, "SetUnitRotations", lua_callback::SetUnitRotations);
		lua_register(m_lua, "GetHero", lua_callback::GetHero);
		lua_register(m_lua, "GiveTaskGotoPoint", GiveTaskGotoPoint);
		lua_register(m_lua, "SetTaskGotoPoint", SetTaskGotoPoint);
		lua_register(m_lua, "CleanTasks", CleanTasks);
		lua_register(m_lua, "GetUnitPosition",GetUnitPosition);
		lua_register(m_lua, "AddModelPaths", AddModelPaths);
		//RendererManager
		lua_register(m_lua, "SetRendereringStyle", lua_callback::SetRenderingStyle);
	}

}

}
