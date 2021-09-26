#pragma once
#include "IAction.h"
#include "Unit.h"

class ActionKillUnit :
	public IAction
{
	class modern_handle m_object;

	ActionKillUnit() = delete;

public:

	ActionKillUnit(class Unit* const object);
	~ActionKillUnit();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};