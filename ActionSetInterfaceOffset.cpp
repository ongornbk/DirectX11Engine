#include "ActionSetInterfaceOffset.h"

#include <modern__.h>

ActionSetInterfaceOffset::ActionSetInterfaceOffset(class Interface* const inter,DirectX::XMFLOAT3& offset)
{
	m_interface.make_handle(inter->GetHandle());
	m_offset = offset;
}

ActionSetInterfaceOffset::ActionSetInterfaceOffset(modern_handle& inter, DirectX::XMFLOAT3& offset)
{
	m_interface.make_handle(inter);
	m_offset = offset;
}

ActionSetInterfaceOffset::~ActionSetInterfaceOffset()
{
}

void ActionSetInterfaceOffset::execute()
{
	class Interface* const A = (class Interface*)m_interface.get();
	if (A)
	{
		modern_guard(m_interface.get());
		A->SetOffset(m_offset);
	}
}

const ActionBehavior ActionSetInterfaceOffset::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
