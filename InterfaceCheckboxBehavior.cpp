#include "InterfaceCheckboxBehavior.h"
#include "UserInterface.h"
#include "LUAManager.h"


InterfaceCheckboxBehavior::InterfaceCheckboxBehavior(Interface* const inter) :
	m_owner(inter)
{
	//m_click = "";
}

InterfaceCheckboxBehavior::~InterfaceCheckboxBehavior()
{

}

void InterfaceCheckboxBehavior::OnHover()
{
	if (m_owner->m_flags.m_selectable)
	{
		float mousePosition[2];
		UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
		DirectX::FXMVECTOR point = XMVectorSet(mousePosition[0], mousePosition[1], 0.0f, 0.0f);
		if (m_owner->m_box.Contains(point))
		{
			m_owner->m_flags.m_selected = true;
			//GLOBAL m_lastSelectedUnit = this;//atomic?
			//m_owner->SetColorFilter(1.5f, 1.5f, 1.5f, 1.f);
			OnClick();
		}
		else
		{
			m_owner->m_flags.m_selected = false;
			//m_owner->SetColorFilter(1.f, 1.f, 1.f, 1.f);
		}
	}
}

void InterfaceCheckboxBehavior::OnClick()
{

	class Input* input = Engine::GetEngine()->GetInput();
	if (input)
	{
		if (input->GetMousePressed(0))
		{
			m_checked = !m_checked;
			if (m_checked)
			{
				m_owner->SetColorFilter(1.5f, 1.5f, 1.5f, 1.f);
			}
			else
			{
				m_owner->SetColorFilter(1.f, 1.f, 1.f, 1.f);
			}
		}
	}
}

const InterfaceBehaviorType InterfaceCheckboxBehavior::GetType() const noexcept
{
	return InterfaceBehaviorType::INTERFACE_BEHAVIOR_TYPE_CHECKBOX;
}
