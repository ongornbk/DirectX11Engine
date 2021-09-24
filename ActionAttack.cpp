#include "ActionAttack.h"
#include "modern/modern_guard.h"
ActionAttack::ActionAttack(class Unit* const object,class Unit* const target) : m_object(object), m_target(target)
{
}

ActionAttack::~ActionAttack()
{
}

void ActionAttack::execute()
{
	class Unit* const A = (Unit*)m_object.get();
	class Unit* const B = (Unit*)m_target.get();
	if (A&&B)
	{
		modern_guard gA(A);
		modern_guard gB(B);
		A->Attack(B);
	}
}

const ActionBehavior ActionAttack::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
