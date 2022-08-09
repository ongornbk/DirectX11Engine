#include "ActionExecuteCFunction.h"

ActionExecuteCFunction::ActionExecuteCFunction(void(*void_f)(void))
{
    m_foo = new class CFunctionVoid(void_f);
}

ActionExecuteCFunction::~ActionExecuteCFunction()
{
    if (m_foo)
    {
        delete m_foo;
        m_foo = nullptr;
    }
}

void ActionExecuteCFunction::execute()
{
    if (m_foo)
    {
        m_foo->execute();
    }
}

const ActionBehavior ActionExecuteCFunction::execute_in_array()
{
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
