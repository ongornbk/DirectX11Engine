#include "ActionAddAlpha.h"

ActionAddAlpha::ActionAddAlpha(class GameObject* const object,const float alpha)
{
	m_object.make_handle(object->GetHandle());
	m_alpha = alpha;
}

ActionAddAlpha::~ActionAddAlpha()
{
}

void ActionAddAlpha::execute()
{
	class GameObject* const A = (class GameObject*)m_object.get();
	if (A)
	{
		if(A->m_type_v2->InheritsFromColorFilter())
		{
			class ColorFilter* const filter = (class ColorFilter* const)(A);
			modern_guard g(A);
			filter->AddAlpha(m_alpha);
		}
	}
}


const ActionBehavior ActionAddAlpha::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
