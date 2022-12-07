#include "TaskUpdateInterface_v5.h"
#include "Camera.h"
#include "Interface.h"

TaskUpdateInterface_v5::TaskUpdateInterface_v5(const modern_handle& __p_interface, const DirectX::XMFLOAT3& offset, const float dt) : m_dt(dt), m_offset(offset)
{
	m_interface.make_handle(__p_interface);
}

TaskUpdateInterface_v5::~TaskUpdateInterface_v5()
{
}

void TaskUpdateInterface_v5::execute()
{
	{
		class Interface* const A = (class Interface* const)m_interface.get();
		if (A)
		{
			modern_guard g(A);
			XMVECTOR offca = Camera::GetCurrentCamera()->GetPosition() + XMLoadFloat3(&m_offset);
			A->SetPosition(offca);
			A->Update(m_dt);

		}
	}
}
