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
		switch (A->m_type)
		{
		case GameObject::EObjectType::OBJECT_TYPE_UNIT:
		{
			goto APPLY;
		}
		case GameObject::EObjectType::OBJECT_TYPE_TREE:
		{
			goto APPLY;
		}
		default:
		{
			break;
		}
		}


		return;
	APPLY:
		class ColorFilter* const AA = dynamic_cast<ColorFilter*>(A);
		if (AA)
		{
			modern_guard g(A);
			AA->AddAlpha(m_alpha);
		}
		else
		{

		}
	}
}


const ActionBehavior ActionAddAlpha::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
