#include "InterfaceStatusBarBehavior.h"

#include "InterfaceCheckboxBehavior.h"
#include "UserInterface.h"
#include "LUAManager.h"
#include "Options.h"

InterfaceStatusBarBehavior::InterfaceStatusBarBehavior(Interface* const inter) :
	m_owner(inter), m_status(1.f)
{

}

InterfaceStatusBarBehavior::~InterfaceStatusBarBehavior()
{

}

void InterfaceStatusBarBehavior::OnHover()
{
	
}

void InterfaceStatusBarBehavior::OnClick()
{

	
}

void InterfaceStatusBarBehavior::SetStatus(const float status)
{
	m_status = status;
	m_owner->m_scale.x = status;
}



const InterfaceBehaviorType InterfaceStatusBarBehavior::GetType() const noexcept
{
	return InterfaceBehaviorType::INTERFACR_BEHAVIOR_TYPE_STATUSBAR;
}
