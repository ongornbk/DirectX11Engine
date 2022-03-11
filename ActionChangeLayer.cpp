#include "ActionChangeLayer.h"
#include "ActionPushObject.h"
#include "Timer.h"
#include "modern/modern_guard.h"

ActionChangeLayer::ActionChangeLayer(class EObject* const object, const enum class RenderLayerType layer)
{
	m_object.make_handle(object->GetHandle());
	m_layer = layer;
}

ActionChangeLayer::~ActionChangeLayer()
{
}

void ActionChangeLayer::execute()
{
	class EObject* const A = (class EObject*)m_object.get();
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
