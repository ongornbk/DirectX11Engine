#pragma once
#include "IAction.h"
#include "Unit.h"

class ActionAttack :
	public IAction
{
	class Unit* m_object;
	class Unit* m_target;

		ActionAttack() = delete;

public:

	ActionAttack(class Unit* const object, class Unit* const target);
	~ActionAttack();

	void execute() override;
};

