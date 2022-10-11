#include "ActionPushObject.h"

ActionPushObject::ActionPushObject(class GameObject* const object, const enum class RenderLayerType layer)
{
	m_object.make_handle(object->GetHandle());
	m_layer = layer;
}

ActionPushObject::~ActionPushObject()
{
}

void ActionPushObject::execute()
{
	class GameObject* const A = (class GameObject*)m_object.get();
	if (A)
	{
		RendererManager::GetInstance()->Push(A, m_layer);
	}
}

const ActionBehavior ActionPushObject::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
