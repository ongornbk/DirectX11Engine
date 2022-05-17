#include "ActionGlobalSetLeavingObject.h"

ActionGlobalSetLeavingObject::ActionGlobalSetLeavingObject(class modern_handle& object)
{
    m_object.make_handle(object);
}

ActionGlobalSetLeavingObject::~ActionGlobalSetLeavingObject()
{
}

void ActionGlobalSetLeavingObject::execute()
{
    Global::GetInstance()->m_leavingObject.make_handle(m_object);
}

const ActionBehavior ActionGlobalSetLeavingObject::execute_in_array()
{
    this->execute();
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
