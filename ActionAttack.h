#pragma once
#include "IAction.h"
#include "Unit.h"
#include "modern/modern_handle.h"

class ActionAttack :
	public IAction
{
	//class Unit* m_object;
	//class Unit* m_target;
	modern_handle m_object;
	modern_handle m_target;

		ActionAttack() = delete;

public:

	ActionAttack(class Unit* const object, class Unit* const target);
	~ActionAttack();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

