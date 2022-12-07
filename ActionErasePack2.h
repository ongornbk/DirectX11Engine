#pragma once
#include "IAction.h"
#include "LuaManager.h"

class ActionErasePack2 :
	public IAction
{
	struct modern_pack2* m_pack;

	ActionErasePack2() = delete;

public:

	ActionErasePack2(struct modern_pack2* const refpackk);
	~ActionErasePack2();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};
