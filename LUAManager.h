#pragma once
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

	namespace lua
	{
		static const char* LUA_LOCATION_INITIALIZATION = "lua/init.lua";

		void       Execute(const char* filename);
		void       Close()                          noexcept;
		void       Open()                           noexcept;
		void       PrintError()                     noexcept;
		void       LoadLuaLibrary()                 noexcept;
		lua_State* GetInstance()                    noexcept;
	}
}
