#include "ActionTreeSetStance.h"

ActionTreeSetStance::ActionTreeSetStance(class Tree* const object, const modern_Boolean stance)
{
	m_tree.make_handle(object->GetHandle());
	m_stance = stance;
}

ActionTreeSetStance::~ActionTreeSetStance()
{
}

void ActionTreeSetStance::execute()
{
	class Tree* const A = (class Tree*)m_tree.get();
	if (A)
	{
		modern_guard g(A);
		A->SetStance(m_stance);
	}
}


const ActionBehavior ActionTreeSetStance::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
