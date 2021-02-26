#include "BooleanVariableObjectIsSelected.h"
#include "RenderContainer.h"
#include <cassert>

BooleanVariableObjectIsSelected::BooleanVariableObjectIsSelected(class EObject * const __object) : object(__object)
{

}

const bool BooleanVariableObjectIsSelected::get()
{
	assert(object);
	if (object)
	{
		return object->m_flags.m_selected;
	}
	return false;
}
