#include "TaskUpdateInterface_v2.h"
#include "Interface.h"
#include "Camera.h"
#include "Unit.h"
#include "InterfaceStatusBarBehavior.h"

TaskUpdateInterface_v2::TaskUpdateInterface_v2(const modern_handle& __p_interface, const modern_handle& focus, const float dt) : m_dt(dt)
{
	m_interface.make_handle(__p_interface);
	m_focus.make_handle(focus);
}

TaskUpdateInterface_v2::~TaskUpdateInterface_v2()
{
}

void TaskUpdateInterface_v2::execute()
{
		class Interface* const A = (class Interface* const)m_interface.get();
		if (A)
		{
			modern_guard g(A);
			A->SetPosition(Camera::GetCurrentCamera()->GetPosition());
			A->Update(m_dt);
			class Unit* const unit = (class Unit* const)m_focus.get();
			if (Unit::CheckIfValid(unit))
			{
				class InterfaceStatusBarBehavior* const behaviorA = (class InterfaceStatusBarBehavior* const)A->GetBehavior();
				modern_shared_guard g(unit);
				const float che = modern_ceil(unit->GetHealth());
				const float mhe = unit->GetMaxHealth();
				//A->SetText(modern_string((int32_t)che, L".", (int32_t)mhe));
				if (behaviorA)
				{
					behaviorA->SetStatusCutYAnchorBottom(che / mhe);
				}
			}
		}
}
