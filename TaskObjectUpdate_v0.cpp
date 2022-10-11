#include "TaskObjectUpdate_v0.h"
#include "GameObject.h"

TaskObjectUpdate_v0::TaskObjectUpdate_v0(const modern_handle& object, const float dt) : m_dt(dt)
{
	m_object.make_handle(object);
}

TaskObjectUpdate_v0::~TaskObjectUpdate_v0()
{
}

void TaskObjectUpdate_v0::execute()
{
	class GameObject* const obj = (class GameObject* const)m_object.get();
	if (obj)
	{
		class modern_guard g(obj);
		obj->Update(m_dt);
	}
}
