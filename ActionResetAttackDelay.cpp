#include "ActionResetAttackDelay.h"
#include "Unit.h"
ActionResetAttackDelay::ActionResetAttackDelay(const modern_handle& handle)
{
	m_object.make_handle(handle);
}

ActionResetAttackDelay::~ActionResetAttackDelay()
{
}

void ActionResetAttackDelay::execute()
{
	//__interface IAttackOwner* const A = (__interface IAttackOwner*)m_object.get();
	//if (A)
	//{
	//	modern_guard guard(m_object.get());
	//	A->GetAttack().delay = false;
	//}

	class Unit* const A = (class Unit*)m_object.get();
	if (A)
	{
		modern_guard guard(A);
		A->GetAttack().delay = false;
	}
}

const ActionBehavior ActionResetAttackDelay::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
