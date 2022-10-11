#include "ActionRemoveObject.h"
#include "modern/modern_guard.h"

ActionRemoveObject::ActionRemoveObject(class GameObject* const object)
{
	m_object.make_handle(object->GetHandle());
}

ActionRemoveObject::~ActionRemoveObject()
{
}

void ActionRemoveObject::execute()
{
	class GameObject* const A = (class GameObject*)m_object.get();
	if (A)
	{
		modern_guard guard(A);
		A->m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DELETE;
		//A->RemoveNow();
		//m_object->Release();
		CleanupFrame();


		//class Global* const global = Global::GetInstance();
		//if (A == global->m_lastSelectedUnit.get())
			//global->m_lastSelectedUnit = nullptr;
		//m_object = nullptr;
	}
}

const ActionBehavior ActionRemoveObject::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
