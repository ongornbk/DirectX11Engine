#include "RenderContainer.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"
#include <iostream>

EObject* const EObject::GetClosestObject() const
{
    return nullptr;
}

const modern_handle& EObject::GetHandle()
{
    return m_object;
}

modern_handle* const EObject::GetHandlePtr()
{
    return &m_object;
}

modern_handle* const EObject::GetNewHandlePtr()
{
    return new modern_handle(m_object);
}

volatile modern_handle& EObject::GetHandle() volatile
{
    return m_object;
}

void EObject::safe_remove() modern_except_state
{
    class ActionExecuteActionArray* const def_actions_array = new class ActionExecuteActionArray();
    def_actions_array->push(new class ActionRemoveObject(this));
    Timer::CreateInstantTimer(def_actions_array);
}

EObject::~EObject()
{
   // std::cout << "Wazzup!";
}
