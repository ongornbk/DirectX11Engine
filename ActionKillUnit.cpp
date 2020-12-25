#include "ActionKillUnit.h"

ActionKillUnit::ActionKillUnit(Unit* const object) : m_object(object)
{
}

ActionKillUnit::~ActionKillUnit()
{
}

void ActionKillUnit::execute()
{
	if (m_object)
	{
		m_object->Die(nullptr);
	}
}

const ActionBehavior ActionKillUnit::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
