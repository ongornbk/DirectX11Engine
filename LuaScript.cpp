#include "LuaScript.h"
#include <cassert>

#pragma comment(lib,"liblua53.a")

LuaScript::LuaScript() : m_state(nullptr)
{
}

LuaScript::~LuaScript()
{
	if (m_state)
	{
		lua_close(m_state);
		m_state = nullptr;
	}
}

void LuaScript::Load(const char* const filename)
{
	m_state = lua::Load(filename);
	assert(m_state);
}

void LuaScript::Execute()
{
	int result;
	if (m_state)
	{
		result = lua_pcall(m_state, 0, LUA_MULTRET, 0);
		if (result != LUA_OK) {
			lua::PrintError();
			return;
		}
	}
}
