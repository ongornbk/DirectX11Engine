#include "ActionApplyColorFilter.h"
#include <iostream>

//ActionApplyColorFilter::ActionApplyColorFilter(Unit* const object, DirectX::XMFLOAT4& color) : m_object(object), m_color(color)
//{
//	//m_stance = ActionStance::ACTION_STANCE_RUNNING;
//}

ActionApplyColorFilter::ActionApplyColorFilter(class EObject* const object, DirectX::XMFLOAT4 color)
{
	m_object.make_handle(object->GetHandle());
	m_color = color;
}

ActionApplyColorFilter::~ActionApplyColorFilter()
{
}

void ActionApplyColorFilter::execute()
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
				AA->SetColorFilter(m_color);
			}
			else
			{

			}
	}
}


const ActionBehavior ActionApplyColorFilter::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
