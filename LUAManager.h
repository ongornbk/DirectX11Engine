#pragma once
#include "modern/modern_def.h"
#include "compilation_header.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


	namespace lua
	{
#ifdef VS_DEBUG_COMPILATION
		static constexpr char* LUA_LOCATION_ENGINE_INITIALIZATION = "x64/Release/bin/x64/lua/Engine_Initialization.lua";
		static constexpr char* LUA_LOCATION_GAMESCENE_INITIALIZATION = "x64/Release/bin/x64/lua/GameScene_Initialization.lua";
		static constexpr char* LUA_LOCATION_GAMESCENE_UPDATE = "x64/Release/bin/x64/lua/GameScene_Update.lua";
		static constexpr char* LUA_LOCATION_MAINMENU_INITIALIZATION = "x64/Release/bin/x64/lua/interface/MainMenu_Initialization.lua";
		static constexpr char* LUA_LOCATION_MAINMENU_UPDATE = "x64/Release/bin/x64/lua/interface/MainMenu_Update.lua";
		static constexpr char* LUA_LOCATION_RENDERAFTER = "x64/Release/bin/x64/lua/Renderafter.lua";
		static constexpr char* LUA_LOCATION_GRAPHICS_INITIALIZATION = "x64/Release/bin/x64/lua/Graphics_Initialization.lua";
		static constexpr char* LUA_LOCATION_SETTINGS = "x64/Release/bin/x64/lua/settings/settings.lua";
#else
		static constexpr char* LUA_LOCATION_ENGINE_INITIALIZATION        = "lua/Engine_Initialization.lua";
		static constexpr char* LUA_LOCATION_GAMESCENE_INITIALIZATION     = "lua/GameScene_Initialization.lua";
		static constexpr char* LUA_LOCATION_GAMESCENE_UPDATE             = "lua/GameScene_Update.lua";
		static constexpr char* LUA_LOCATION_MAINMENU_INITIALIZATION      = "lua/interface/MainMenu_Initialization.lua";
		static constexpr char* LUA_LOCATION_MAINMENU_UPDATE              = "lua/interface/MainMenu_Update.lua";
		static constexpr char* LUA_LOCATION_RENDERAFTER                  = "lua/Renderafter.lua";
		static constexpr char* LUA_LOCATION_GRAPHICS_INITIALIZATION      = "lua/Graphics_Initialization.lua";
		static constexpr char* LUA_LOCATION_SETTINGS                     = "lua/settings/settings.lua";
#endif // VS_DEBUG_COMPILATION



		 void       Execute(const char* filename);
		 void       Close()                          modern_except_state;
		 void       Open()                           modern_except_state;
		 void       PrintError()                     modern_except_state;
		 void       LoadLuaLibrary()                 modern_except_state;
		 struct lua_State* const Load(const char* const filename) modern_except_state;
		extern struct lua_State* const GetInstance()                    modern_except_state;
	}
}