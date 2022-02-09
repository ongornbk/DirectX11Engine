#include "InterfaceButtonBehavior.h"
#include "UserInterface.h"
#include "LUAManager.h"


InterfaceButtonBehavior::InterfaceButtonBehavior(Interface* const inter) : 
m_owner(inter)
{
	m_click = "";
}

InterfaceButtonBehavior::~InterfaceButtonBehavior()
{

}

void InterfaceButtonBehavior::OnHover()
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
			m_owner->SetColorFilter(1.5f, 1.5f, 1.5f, 1.f);
			OnClick();
		}
		else
		{
			m_owner->m_flags.m_selected = false;
			m_owner->SetColorFilter(1.f, 1.f, 1.f, 1.f);
		}
	}
}

void InterfaceButtonBehavior::OnClick()
{

	class Input* input = Engine::GetEngine()->GetInput();
	if (input)
	{
		if (input->GetMousePressed(0))
		{
			if (m_click.length())
			{

				lua_State* const lua = lua::GetInstance();
				lua_getglobal(lua, m_click.c_str());
				lua_pcall(lua, 0, 0, 0);
			}
		}
	}
}

const InterfaceBehaviorType InterfaceButtonBehavior::GetType() const noexcept
{
	return InterfaceBehaviorType::INTERFACE_BEHAVIOR_TYPE_BUTTON;
}

void InterfaceButtonBehavior::SetOnClick(std::string click)
{
	m_click = click;
}
