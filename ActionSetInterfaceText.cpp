#include "ActionSetInterfaceText.h"

ActionSetInterfaceText::ActionSetInterfaceText(Interface* const inter, string text) : m_interface(inter), m_text(text)
{
}

ActionSetInterfaceText::~ActionSetInterfaceText()
{
}

void ActionSetInterfaceText::execute()
{
	if (m_interface)
	{
		m_interface->SetText(m_text);
	}
}

const ActionBehavior ActionSetInterfaceText::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
