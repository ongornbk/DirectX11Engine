#include "ActionSetInterfaceText.h"

ActionSetInterfaceText::ActionSetInterfaceText(Interface* const inter, string text,const float size) : m_interface(inter), m_text(text), m_size(size)
{
}

ActionSetInterfaceText::~ActionSetInterfaceText()
{
}

void ActionSetInterfaceText::execute()
{
	if (m_interface)
	{
		modern_guard g(m_interface);
		m_interface->SetText(m_text,m_size);
		m_interface->PostInitializeText();
	}
}

const ActionBehavior ActionSetInterfaceText::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
