#include "ActionRemoveObject.h"
ActionRemoveObject::ActionRemoveObject(class EObject* const object) : m_object(object)
{
}

ActionRemoveObject::~ActionRemoveObject()
{
}

void ActionRemoveObject::execute()
{
	if (m_object)
	{
		m_object->Release();
		CleanupFrame();
		class Global* const global = Global::GetInstance();
		if (m_object == global->m_lastSelectedUnit)
			global->m_lastSelectedUnit = nullptr;
		m_object = nullptr;
	}
}
