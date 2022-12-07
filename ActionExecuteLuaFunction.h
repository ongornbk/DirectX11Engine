
#pragma once
#include "IAction.h"
#include "LuaManager.h"

class ActionExecuteLuaFunction :
	public IAction
{
	struct lua_State* m_lua;
	modern_cstring    m_foo;

	ActionExecuteLuaFunction() = delete;

public:

	ActionExecuteLuaFunction(struct lua_State* const lua,modern_cstring& fooname);
	~ActionExecuteLuaFunction();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};
