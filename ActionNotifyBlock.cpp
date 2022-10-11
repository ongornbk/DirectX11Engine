#include "ActionNotifyBlock.h"
#include "modern/modern_guard.h"

ActionNotifyBlock::ActionNotifyBlock(class Unit* const object,class GameObject* const other)
{
	m_object.make_handle(object->GetHandle());
	m_other.make_handle(other->GetHandle());
}

ActionNotifyBlock::~ActionNotifyBlock()
{
}

void ActionNotifyBlock::execute()
{
	class Unit* const A = (class Unit* const)m_object.get();
	class GameObject* const B = (class GameObject* const)m_other.get();
	if (A&&B)
	{
		modern_guard guardA(A);
		modern_guard guardB(B);
		A->NotifyBlock(B);
	}
}

const ActionBehavior ActionNotifyBlock::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
