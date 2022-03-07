#include "BooleanVariableObjectIsSelected.h"
#include "RenderContainer.h"
#include <cassert>

BooleanVariableObjectIsSelected::BooleanVariableObjectIsSelected(class EObject * const __object)
{
	object.make_handle(__object->GetHandle());
}

const bool BooleanVariableObjectIsSelected::get()
{
	class EObject* const A = (class EObject* const)object.get();
	if (A)
	{
		modern_shared_guard g(A);
		return A->m_flags.m_selected;
	}
	return false;
}
