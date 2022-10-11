#include "BooleanVariableObjectIsSelected.h"
#include "GameObject.h"
#include <cassert>

BooleanVariableObjectIsSelected::BooleanVariableObjectIsSelected(class GameObject * const __object)
{
	object.make_handle(__object->GetHandle());
}

const bool BooleanVariableObjectIsSelected::get()
{
	class GameObject* const A = (class GameObject* const)object.get();
	if (A)
	{
		modern_shared_guard g(A);
		return A->m_flags.m_selected;
	}
	return false;
}
