#include "ActionExecuteLuaFunction.h"

#include <modern__.h>

ActionExecuteLuaFunction::ActionExecuteLuaFunction(lua_State* const lua, modern_cstring& fooname)
{
	m_lua = lua;
	m_foo = fooname;
}

ActionExecuteLuaFunction::~ActionExecuteLuaFunction()
{
}

void ActionExecuteLuaFunction::execute()
{
	lua_pcall(m_lua, 0, 0, 0);
	lua_getglobal(m_lua, m_foo.c_str());
	lua_pcall(m_lua, 0, 0, 0);
}

const ActionBehavior ActionExecuteLuaFunction::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
