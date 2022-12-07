#include "ActionSetInterfaceBehavior.h"

#include <modern__.h>

ActionSetInterfaceBehavior::ActionSetInterfaceBehavior(modern_handle& inter, class IInterfaceBehavior* const behavior)
{
	m_interface.make_handle(inter);
	m_behavior = behavior;
}

ActionSetInterfaceBehavior::~ActionSetInterfaceBehavior()
{
}

void ActionSetInterfaceBehavior::execute()
{
	class Interface* const A = (class Interface*)m_interface.get();
	if (A)
	{
		modern_guard(m_interface.get());
		A->SetBehavior(m_behavior);
	}
}

const ActionBehavior ActionSetInterfaceBehavior::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
