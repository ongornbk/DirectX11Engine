#include "LUAManager.h"
#include <Windows.h>
#define LUA_LOCATION "lua53.dll"

extern "C"
{
	namespace
	{
		static lua_State* m_instance = NULL;
		static HINSTANCE  m_iddl = NULL;
	}

	namespace lua
	{

		void LoadLuaLibrary()
		{
			m_iddl = LoadLibrary(LUA_LOCATION);
		}

		void Open() noexcept
		{
			if (m_instance)
			{
				lua::Close();
			}
			m_instance = luaL_newstate();
		}

		void Close() noexcept
		{
			if (m_instance)
			{
				lua_close(m_instance);
				m_instance = NULL;
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
			puts(message);
			lua_pop(m_instance,1);
		}

		lua_State* GetInstance() noexcept
		{
			return m_instance; //UNSAFE
		}

	}

}

