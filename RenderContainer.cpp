#include "RenderContainer.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"
#include <iostream>

const modern_handle& EObject::GetHandle()
{
    return m_object;
}

volatile modern_handle& EObject::GetHandle() volatile
{
    return m_object;
}

void EObject::safe_remove() noexcept
{
    class ActionExecuteActionArray* const def_actions_array = new class ActionExecuteActionArray();
    def_actions_array->push(new class ActionRemoveObject(this));
    Timer::CreateInstantTimer(def_actions_array);
}

EObject::~EObject()
{
   // std::cout << "Wazzup!";
}
