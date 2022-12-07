#include "ActionKillUnit.h"

#include <modern__.h>

ActionKillUnit::ActionKillUnit(Unit* const object)
{
	m_object.make_handle(object->GetHandle());
}

ActionKillUnit::~ActionKillUnit()
{
}

void ActionKillUnit::execute()
{
	class Unit* const A = (class Unit*)m_object.get();
	if (A)
	{
		modern_guard guard(A);
		A->Die(nullptr);
	}
}

const ActionBehavior ActionKillUnit::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
