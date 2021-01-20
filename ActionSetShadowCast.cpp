#include "ActionSetShadowCast.h"



ActionSetShadowCast::ActionSetShadowCast(class EObject* const object, bool shadow) : m_object(object), m_shadowCast(shadow)
{
}

ActionSetShadowCast::~ActionSetShadowCast()
{
}

void ActionSetShadowCast::execute()
{
	if (m_object)
	{
		m_object->m_flags.m_cast_shadow = m_shadowCast;
	}
}

const ActionBehavior ActionSetShadowCast::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
