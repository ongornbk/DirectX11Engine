#include "ResourceManager.h"
#include "LUAManager.h"
#include "Camera.h"
#include "SettingsC.h"
#include "Engine.h"

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
	static void SetDirectX(DXManager* manager);

	namespace
	{

		static ResourceManager* m_resources;
		static Camera*          m_camera;
		static Engine*          m_engine;
		static Input*           m_input;
		static DXManager*       m_directX;
		

	}

	static void SetResourceManager(ResourceManager* manager)
	{
		m_resources = manager;
	}

	static void SetCamera(Camera* camera)
	{
		m_camera = camera;
	}

	static void Initialize(Engine* engine)
	{
		m_engine = engine;
	}

	static void SetInput(Input* input)
	{
		m_input = input;
	}

	static void SetDirectX(DXManager* manager)
	{
		m_directX = manager;
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
		return 1;
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
		return 1;
	}


	static int InitializeProjectionMatrix(lua_State* state) //EXPORTED
	{
		m_camera->InitializeProjectionMatrix((float)XM_PI / LUA_FLOAT(state, 1), Settings::GetAspectRatio(),1.0 / LUA_FLOAT(state, 2), LUA_FLOAT(state, 3));
		return 1;
	}

	static int InitializeOrthoMatrix(lua_State* state) //EXPORTED
	{
		m_camera->InitializeOrthoMatrix(*(Settings::get()->RESOLUTION_X), *(Settings::get()->RESOLUTION_Y), 1.0 / LUA_FLOAT(state, 1), LUA_FLOAT(state, 2));
		return 1;
	}

	static int SetCameraPosition(lua_State* state) //EXPORTED
	{
		XMVECTOR position;
		position.m128_f32[0] = LUA_FLOAT(state, 1);
		position.m128_f32[1] = LUA_FLOAT(state, 2);
		position.m128_f32[2] = LUA_FLOAT(state, 3);
		m_camera->SetPosition(position);
		return 1;
	}

	static int AddMusic(lua_State* state) //EXPORTED
	{
#pragma warning(disable : 4996)
		string str = LUA_STRING(state, 1);

		wchar_t* wide_string = new wchar_t[str.length() + 1];
		wstring ws = std::wstring(str.begin(), str.end()).c_str();
		wcscpy(wide_string, ws.c_str());
		m_engine->AddMusic(wide_string, LUA_FLOAT(state, 2), LUA_BOOLEAN(state, 3));
		delete wide_string;
		return 1;
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
		return 1;
	}

	static int __PostQuitMessage(lua_State* state) //EXPORTED
	{
		PostQuitMessage(lua_tointeger(state,1));
		return 1;
	}

	static int __IsKeyHit(lua_State* state) //EXPORTED
	{
		if (m_input->IsKeyHit(lua_tointeger(state,1)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	static int InitializeDirectX(lua_State* state)
	{
		m_directX->SetSettings(LUA_BOOLEAN(state, 1), LUA_BOOLEAN(state,2));
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
		//Music
		lua_register(m_lua, "AddMusic", lua_callback::AddMusic);
		lua_register(m_lua, "PlayMusic", lua_callback::PlayMusic);
		//System
		lua_register(m_lua, "PostQuitMessage", lua_callback::__PostQuitMessage);
		//Input
		lua_register(m_lua, "IsKeyHit", __IsKeyHit);
		//Graphics
		lua_register(m_lua, "InitializeDirectX", InitializeDirectX);

	}

}

}
