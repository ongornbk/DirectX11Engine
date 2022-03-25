#include "ActionGoBack.h"
#include "modern/modern_guard.h"

ActionGoBack::ActionGoBack(Unit* const object)
{
	m_object.make_handle(object->GetHandle());
}

ActionGoBack::~ActionGoBack()
{
}

void ActionGoBack::execute()
{
	class Unit* const A = (class Unit*)m_object.get();
	if (A)
	{
		modern_guard guard(A);
		A->GoBack();
	}
}

const ActionBehavior ActionGoBack::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
