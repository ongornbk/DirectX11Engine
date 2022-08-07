#include "ActionShowInterface.h"

ActionShowInterface::ActionShowInterface(Interface* const inter, const modern_Boolean value)
{
	m_interface.make_handle(inter->GetHandle());
	m_value = value;
}

ActionShowInterface::ActionShowInterface(const modern_handle& inter, const modern_Boolean value)
{
	m_interface.make_handle(inter);
	m_value = value;
}

ActionShowInterface::~ActionShowInterface()
{
}

void ActionShowInterface::execute()
{
	class Interface* const A = (class Interface*)m_interface.get();
	if (A)
	{
		modern_guard(m_interface.get());
		A->Show(m_value);
	}
}

const ActionBehavior ActionShowInterface::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
