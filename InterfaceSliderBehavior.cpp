#include "InterfaceSliderBehavior.h"
#include "UserInterface.h"
#include "LUAManager.h"
#include "Options.h"
#include "IPP.h"
#include "modern/modern_types.h"

InterfaceSliderBehavior::InterfaceSliderBehavior(Interface* const owner) :
	m_owner(owner), m_checked(0)
{
	ID3D11Device* const device = Engine::GetEngine()->GetGraphics()->GetDevice();
	ID3D11DeviceContext* const context = Engine::GetEngine()->GetGraphics()->GetDeviceContext();
	//Shader* const m_unitsShader = (class TextureShader*)ResourceManager::GetInstance()->GetShaderByName("units.fx");
	Shader* const m_interfaceShader = (class TextureShader*)ResourceManager::GetInstance()->GetShaderByName("interface.fx");
	Shader* const m_textShader = (class TextureShader*)ResourceManager::GetInstance()->GetShaderByName("text.fx");

	m_button = new class Interface();
	m_button->SetParent(m_owner);
	m_owner->PushChild(m_button);
	m_button->m_flags.m_rendering = true;
	m_button->Initialize(device, context, m_interfaceShader, m_textShader, L"slider_button", m_owner->m_boundingSphere.Center,38.f,29.f,ObjectAnchorType::OBJECT_ANCHOR_TYPE_CENTER);
}

InterfaceSliderBehavior::~InterfaceSliderBehavior()
{
}

void InterfaceSliderBehavior::OnHover()
{
	if (m_owner->m_flags.m_selectable)
	{
		float mousePosition[2];
		UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
		DirectX::FXMVECTOR point = XMVectorSet(mousePosition[0], mousePosition[1], 0.0f, 0.0f);
		DirectX::BoundingBox box = m_owner->m_box;
		box.Extents.x -= 58.f;
		box.Center.x -= 9.f;
		if (box.Contains(point))
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

void InterfaceSliderBehavior::OnClick()
{

	class Input* input = Engine::GetEngine()->GetInput();
	if (input)
	{
		if (input->GetMouseState(0))
		{
			if (m_key >= 0)
			{
				modern_handle opth;
				opth.make_handle(Options::GetInstance());
				class Options* const options = (class Options* const)(opth.get());
				if (options)
				{
					modern_guard g(options);
					float mousePosition[2];
					UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
					m_button->SetOffset(DirectX::XMFLOAT3{ mousePosition[0],0.f,0.f });
					options->options[m_key] = m_checked;
					
					//modern_as_percentage distanceA = modern_abs((m_owner->m_box.Center.x - m_owner->m_box.Extents.x) - mousePosition[0]);
					//modern_as_percentage percent = mousePosition[0];
					float left = m_owner->m_box.Center.x -9.f - (m_owner->m_box.Extents.x - 58.f);
					float right = m_owner->m_box.Center.x -9.f + (m_owner->m_box.Extents.x - 58.f);
					float mouse = mousePosition[0];
					float width = m_owner->m_width;
					float internal_width = modern_abs(left - right);
					float percentage = (mouse + (m_owner->m_box.Extents.x - 58.f)) / internal_width * 100.f;

					ipp::Console::Println(modern_string(modern_variable_name(left)) << modern_string(L": ") << modern_string(left),MODERN_CONSOLE_TEXT_COLOR::BLUE);
					ipp::Console::Println(modern_string(modern_variable_name(right)) << modern_string(L": ") << modern_string(right), MODERN_CONSOLE_TEXT_COLOR::BLUE);
					ipp::Console::Println(modern_string(modern_variable_name(mouse)) << modern_string(L": ") << modern_string(mouse), MODERN_CONSOLE_TEXT_COLOR::BLUE);
					ipp::Console::Println(modern_string(modern_variable_name(width)) << modern_string(L": ") << modern_string(width), MODERN_CONSOLE_TEXT_COLOR::BLUE);
					ipp::Console::Println(modern_string(modern_variable_name(internal_width)) << modern_string(L": ") << modern_string(internal_width), MODERN_CONSOLE_TEXT_COLOR::BLUE);
					ipp::Console::Println(modern_string(modern_variable_name(percentage)) << modern_string(L": ") << modern_string(percentage), MODERN_CONSOLE_TEXT_COLOR::BLUE);
				}
			}

		}
	}
}

void InterfaceSliderBehavior::Bind(const modern_cstring& option)
{
	modern_handle opth;
	opth.make_handle(Options::GetInstance());
	class Options* const options = (class Options* const)(opth.get());
	if (options)
	{
		modern_shared_guard g(options);
		m_key = options->GetKey(option);





		m_checked = options->options[m_key];
	}
}

const InterfaceBehaviorType InterfaceSliderBehavior::GetType() const modern_except_state
{
	return InterfaceBehaviorType::INTERFACE_BEHAVIOR_TYPE_SLIDER;
}
