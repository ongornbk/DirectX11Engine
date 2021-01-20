#pragma once
#include "LUAManager.h"
#include "IScript.h"

class LuaScript :
	public IScript
{
	struct lua_State* m_state;
public:
	LuaScript();
	~LuaScript();

	void Load(const char* const filename) override;
	void Execute() override;
};

