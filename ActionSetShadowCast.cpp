#include "ActionSetShadowCast.h"
#include "modern/modern_guard.h"


ActionSetShadowCast::ActionSetShadowCast(class EObject* const object, bool shadow)
{
	m_object.make_handle(object->GetHandle());
	m_shadowCast = shadow;
}

ActionSetShadowCast::~ActionSetShadowCast()
{
}

void ActionSetShadowCast::execute()
{
	class EObject* const A = (class EObject*)m_object.get();
	if (A)
	{
		modern_guard guard(A);
		A->m_flags.m_cast_shadow = m_shadowCast;
	}
}

const ActionBehavior ActionSetShadowCast::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
