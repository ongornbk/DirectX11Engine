#include "ActionSetTextAlignment.h"
#include "Text.h"

ActionSetTextAlignment::ActionSetTextAlignment(class modern_handle& text, const enum class TextAlignment alignment) : m_align(alignment)
{
    m_text.make_handle(text);
}

ActionSetTextAlignment::~ActionSetTextAlignment()
{
}

void ActionSetTextAlignment::execute()
{

        class Text* const A = (class Text*)m_text.get();
        if (A)
        {
            modern_guard g(A);
            A->SetAlignment(m_align);
        }
    }

const ActionBehavior ActionSetTextAlignment::execute_in_array()
{
    this->execute();
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}

