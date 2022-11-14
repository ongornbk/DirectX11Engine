#include "ActionApplyColorFilter.h"
#include <iostream>

//ActionApplyColorFilter::ActionApplyColorFilter(Unit* const object, DirectX::XMFLOAT4& color) : m_object(object), m_color(color)
//{
//	//m_stance = ActionStance::ACTION_STANCE_RUNNING;
//}

ActionApplyColorFilter::ActionApplyColorFilter(class GameObject* const object, DirectX::XMFLOAT4 color)
{
	m_object.make_handle(object->GetHandle());
	m_color = color;
}

ActionApplyColorFilter::~ActionApplyColorFilter()
{
}

void ActionApplyColorFilter::execute()
{
	class GameObject* const A = (class GameObject*)m_object.get();
	if (A)
	{
		if (A->m_type_v2->InheritsFromColorFilter())
		{
			class ColorFilter* const filter = (class ColorFilter* const)(A);
			modern_guard g(A);
			filter->SetColorFilter(m_color);
		}
	}
}


const ActionBehavior ActionApplyColorFilter::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
