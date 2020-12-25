#include "ActionChangeLayer.h"
#include "ActionPushObject.h"
#include "Timer.h"

ActionChangeLayer::ActionChangeLayer(class EObject* const object, const enum class RenderLayerType layer) : m_object(object), m_layer(layer)
{
}

ActionChangeLayer::~ActionChangeLayer()
{
}

void ActionChangeLayer::execute()
{
	if (m_object)
	{
		m_object->m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_REMOVE;
		CleanupFrame();
		//RendererManager::GetInstance()->Push(m_object, m_layer);
		Timer::CreateInstantTimer(new ActionPushObject(m_object, m_layer));
	}
}

const ActionBehavior ActionChangeLayer::execute_in_array()
{
	this->execute();

	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
