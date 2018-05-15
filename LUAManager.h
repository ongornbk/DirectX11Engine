#pragma once
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

	namespace lua
	{
		static const char* LUA_LOCATION_ENGINE_INITIALIZATION    = "lua/Engine_Initialization.lua";
		static const char* LUA_LOCATION_GAMESCENE_INITIALIZATION = "lua/GameScene_Initialization.lua";
		static const char* LUA_LOCATION_GAMESCENE_UPDATE         = "lua/GameScene_Update.lua";
		static const char* LUA_LOCATION_GRAPHICS_INITIALIZATION  = "lua/Graphics_Initialization.lua";

		void       Execute(const char* filename);
		void       Close()                          noexcept;
		void       Open()                           noexcept;
		void       PrintError()                     noexcept;
		void       LoadLuaLibrary()                 noexcept;
		lua_State* GetInstance()                    noexcept;
	}
}
