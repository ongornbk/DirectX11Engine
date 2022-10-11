#include "GameObject.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"
#include <iostream>

GameObject* const GameObject::GetClosestObject() const
{
    return nullptr;
}

const modern_handle& GameObject::GetHandle()
{
    return m_object;
}

modern_handle* const GameObject::GetHandlePtr()
{
    return &m_object;
}

modern_handle* const GameObject::GetNewHandlePtr()
{
    return new modern_handle(m_object);
}

volatile modern_handle& GameObject::GetHandle() volatile
{
    return m_object;
}

void GameObject::safe_remove() modern_except_state
{
    class ActionExecuteActionArray* const def_actions_array = new class ActionExecuteActionArray();
    def_actions_array->push(new class ActionRemoveObject(this));
    Timer::CreateInstantTimer(def_actions_array);
}

GameObject::~GameObject()
{

}
