#include "TaskUpdateInterface_v3.h"
#include "Interface.h"
#include "Camera.h"
#include "Unit.h"
#include "InterfaceStatusBarBehavior.h"

TaskUpdateInterface_v3::TaskUpdateInterface_v3(const modern_handle& __p_interface, const modern_handle& focus, const float dt) : m_dt(dt)
{
	m_interface.make_handle(__p_interface);
	m_focus.make_handle(focus);
}

TaskUpdateInterface_v3::~TaskUpdateInterface_v3()
{
}

void TaskUpdateInterface_v3::execute()
{
		class Interface* const A = (class Interface*)m_interface.get();
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
				const float che = modern_ceil(unit->GetMana());
				const float mhe = unit->GetMaxMana();
				//A->SetText(modern_string((int32_t)che, L".", (int32_t)mhe));
				if (behaviorA)
				{
					behaviorA->SetStatusCutYAnchorBottom(che / mhe);
				}
			}
		}
}
