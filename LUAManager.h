#pragma once
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

	namespace lua
	{
		void       Open()           noexcept;
		void       Close()          noexcept;
		void       PrintError()     noexcept;
		void       LoadLuaLibrary() noexcept;
		lua_State* GetInstance()    noexcept;
	}
}
