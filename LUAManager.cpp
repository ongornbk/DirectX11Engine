#include "LUAManager.h"
#include <Windows.h>
#include <map>
#include "IPP.h"
#define LUA_LOCATION "lua53.dll"

#pragma comment(lib,"liblua53.a")

extern "C"
{
#pragma region
	using std::map;
#pragma endregion
	namespace
	{
		static lua_State* m_instance = NULL;
		static HINSTANCE  m_iddl = NULL;
	}

	namespace lua
	{

		void LoadLuaLibrary()
		{
			//m_iddl = LoadLibrary(LUA_LOCATION);
		}

		lua_State* const Load(const char* const filename) modern_except_state
		{
			int result;
			struct lua_State* const state = luaL_newstate();
			luaL_openlibs(state);
			result = luaL_loadfile(state, filename);
			if (result != LUA_OK) {
				lua::PrintError();
				return nullptr;
			}
			return state;
		}



		void Close() modern_except_state
		{
			if (m_instance)
			{
				lua_close(m_instance);
				m_instance = nullptr;
			}
			if (m_iddl)
			{
				delete m_iddl;
				m_iddl = NULL;
			}
		}

		void PrintError() modern_except_state
		{
			const char* message = lua_tostring(m_instance, -1);
			if(message)
			ipp::Console::Println(message);
			lua_pop(m_instance,1);
		}

		struct lua_State* const GetInstance() modern_except_state //UNSAFE
		{
			return m_instance;
		}

		void Open() modern_except_state
		{
			m_instance = luaL_newstate();
			luaL_openlibs(m_instance);
		}

		lua_State* GetInstance_s() modern_except_state //SAFE
		{
			if (m_instance)
			{
				return m_instance;
			}
			else
			{
				lua::Open();
				
			}
			return m_instance;
		}

		void Execute(const char* const filename)
		{
			int result;
			result = luaL_loadfile(m_instance, filename);
			if (result != LUA_OK) {
				lua::PrintError();
				return;
			}
			//result = luaL_loadbuffer(m_instance, filename,strlen(filename),"filename");
			//if (result != LUA_OK) {
			//	lua::PrintError();
			//	return;
			//}
			//luaL_dostring(m_instance, "filename");
			result = lua_pcall(m_instance, 0, LUA_MULTRET, 0);
			if (result != LUA_OK) {
				lua::PrintError();
				return;
			}
		}

		void RegisterFunction(void* function)
		{

		}

	}

}

