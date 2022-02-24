#include "ActionAddAlpha.h"

ActionAddAlpha::ActionAddAlpha(class EObject* const object,const float alpha)
{
	m_object.make_handle(object->GetHandle());
	m_alpha = alpha;
}

ActionAddAlpha::~ActionAddAlpha()
{
}

void ActionAddAlpha::execute()
{
	class EObject* const A = (class EObject*)m_object.get();
	if (A)
	{
		switch (A->m_type)
		{
		case EObject::EObjectType::OBJECT_TYPE_UNIT:
		{
			goto APPLY;
		}
		case EObject::EObjectType::OBJECT_TYPE_TREE:
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
