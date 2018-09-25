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



		void Close() noexcept
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

		void PrintError() noexcept
		{
			const char* message = lua_tostring(m_instance, -1);
			ipp::Console::Println(message);
			lua_pop(m_instance,1);
		}

		lua_State* GetInstance() noexcept //UNSAFE
		{
			return m_instance;
		}

		void Open() noexcept
		{
			m_instance = luaL_newstate();
			luaL_openlibs(m_instance);
		}

		lua_State* GetInstance_s() noexcept //SAFE
		{
			if (m_instance)
			{
				return m_instance;
			}
			else
			{
				lua::Open();
			}
		}

		void Execute(const char* filename)
		{
			int result;
			result = luaL_loadfile(m_instance, filename);
			if (result != LUA_OK) {
				lua::PrintError();
				return;
			}
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

