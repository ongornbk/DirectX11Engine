#include "ActionChangeLayer.h"
#include "ActionPushObject.h"
#include "Timer.h"

#include <modern__.h>

ActionChangeLayer::ActionChangeLayer(class GameObject* const object, const enum class RenderLayerType layer)
{
	m_object.make_handle(object->GetHandle());
	m_layer = layer;
}

ActionChangeLayer::~ActionChangeLayer()
{
}

void ActionChangeLayer::execute()
{
	class GameObject* const A = (class GameObject*)m_object.get();
	if (A)
	{
		modern_guard g(A);
		A->m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_REMOVE;
		CleanupFrame();
		Timer::CreateInstantTimer(new ActionPushObject(A, m_layer));
	}
}

const ActionBehavior ActionChangeLayer::execute_in_array()
{
	this->execute();

	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
