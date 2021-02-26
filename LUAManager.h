#pragma once


extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


	namespace lua
	{
		static constexpr char* LUA_LOCATION_ENGINE_INITIALIZATION    = "x64/Release/bin/x64/lua/Engine_Initialization.lua";
		static constexpr char* LUA_LOCATION_GAMESCENE_INITIALIZATION = "x64/Release/bin/x64/lua/GameScene_Initialization.lua";
		static constexpr char* LUA_LOCATION_GAMESCENE_UPDATE         = "x64/Release/bin/x64/lua/GameScene_Update.lua";
		static constexpr char* LUA_LOCATION_MAINMENU_INITIALIZATION  = "x64/Release/bin/x64/lua/interface/MainMenu_Initialization.lua";
		static constexpr char* LUA_LOCATION_MAINMENU_UPDATE          = "x64/Release/bin/x64/lua/interface/MainMenu_Update.lua";
		static constexpr char* LUA_LOCATION_RENDERAFTER              = "x64/Release/bin/x64/lua/Renderafter.lua";
		static constexpr char* LUA_LOCATION_GRAPHICS_INITIALIZATION  = "x64/Release/bin/x64/lua/Graphics_Initialization.lua";
		static constexpr char* LUA_LOCATION_SETTINGS                 = "x64/Release/bin/x64/lua/settings/settings.lua";

		 void       Execute(const char* filename);
		 void       Close()                          noexcept;
		 void       Open()                           noexcept;
		 void       PrintError()                     noexcept;
		 void       LoadLuaLibrary()                 noexcept;
		 struct lua_State* const Load(const char* const filename) noexcept;
		 struct lua_State* const GetInstance()                    noexcept;
	}
}