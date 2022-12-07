#include "TaskUpdateInterface_v0.h"
#include "Interface.h"
#include "Camera.h"

TaskUpdateInterface_v0::TaskUpdateInterface_v0(const modern_handle& __p_interface,const float dt) : m_dt(dt)
{
	m_interface.make_handle(__p_interface);
}

TaskUpdateInterface_v0::~TaskUpdateInterface_v0()
{
}

void TaskUpdateInterface_v0::execute()
{
	class Interface* const A = (class Interface* const)m_interface.get();
	if (A)
	{
		modern_guard g(A);
		A->SetPosition(Camera::GetCurrentCamera()->GetPosition());
		A->Update(m_dt);
	}
}
