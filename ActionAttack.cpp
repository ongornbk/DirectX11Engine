#include "ActionAttack.h"

ActionAttack::ActionAttack(class Unit* const object,class Unit* const target) : m_object(object), m_target(target)
{
}

ActionAttack::~ActionAttack()
{
}

void ActionAttack::execute()
{
	if (m_object&&m_target)
	{
		m_object->Attack(m_target);
	}
}

const ActionBehavior ActionAttack::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
