#pragma once
#include "IAction.h"

class ActionErasePack4 :
	public IAction
{
	struct modern_pack4* m_pack;

	ActionErasePack4() = delete;

public:

	ActionErasePack4(struct modern_pack4* const refpack);
	~ActionErasePack4();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};
