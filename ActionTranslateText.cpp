#include "ActionTranslateText.h"
#include "Text.h"

#include <modern__.h>

ActionTranslateText::ActionTranslateText(class modern_handle& object, DirectX::XMFLOAT3 position)
{
	m_object.make_handle(object);
	m_vec = position;
}

ActionTranslateText::~ActionTranslateText()
{
}

void ActionTranslateText::execute()
{
	class Text* const A = (class Text*)m_object.get();
		if (A)
		{
			modern_guard g(A);
			A->Translate(m_vec);
		}
}


const ActionBehavior ActionTranslateText::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
