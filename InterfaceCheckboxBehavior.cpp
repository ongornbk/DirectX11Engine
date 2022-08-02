#include "InterfaceCheckboxBehavior.h"
#include "UserInterface.h"
#include "LUAManager.h"
#include "Options.h"

InterfaceCheckboxBehavior::InterfaceCheckboxBehavior(Interface* const inter) :
	m_owner(inter), m_checked(0)
{
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
			if (m_key >= 0)
			{
				modern_handle opth;
				opth.make_handle(Options::GetInstance());
				volatile Options* const options = dynamic_cast<volatile Options* const>(opth.get());
				if (options)
				{
					m_checked = !m_checked;
					modern_guard g(options);
					options->options[m_key] = m_checked;
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
			else
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
}

void InterfaceCheckboxBehavior::Bind(const modern_cstring& option)
{
	modern_handle opth;
	opth.make_handle(Options::GetInstance());
	volatile Options* const options = dynamic_cast<volatile Options* const>(opth.get());
	if (options)
	{
		modern_shared_guard g(options);
		m_key = options->GetKey(option);





		m_checked = options->options[m_key];
	}
}

const InterfaceBehaviorType InterfaceCheckboxBehavior::GetType() const modern_except_state
{
	return InterfaceBehaviorType::INTERFACE_BEHAVIOR_TYPE_CHECKBOX;
}
