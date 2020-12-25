#include "ActionPushObject.h"

ActionPushObject::ActionPushObject(class EObject* const object, const enum class RenderLayerType layer) : m_object(object), m_layer(layer)
{
}

ActionPushObject::~ActionPushObject()
{
}

void ActionPushObject::execute()
{
	if (m_object)
	{
		RendererManager::GetInstance()->Push(m_object, m_layer);
	}
}

const ActionBehavior ActionPushObject::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
