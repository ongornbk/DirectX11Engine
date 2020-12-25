#include "ActionApplyColorFilter.h"

ActionApplyColorFilter::ActionApplyColorFilter(Unit* const object, DirectX::XMFLOAT4& color) : m_object(object), m_color(color)
{
	//m_stance = ActionStance::ACTION_STANCE_RUNNING;
}

ActionApplyColorFilter::~ActionApplyColorFilter()
{
}

void ActionApplyColorFilter::execute()
{
	if (m_object)
	{
		m_object->SetColorFilter(m_color);
	}
}

const ActionBehavior ActionApplyColorFilter::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
