#include "InterfaceStatusBarBehavior.h"

#include "InterfaceCheckboxBehavior.h"
#include "UserInterface.h"
#include "LUAManager.h"
#include "Options.h"

InterfaceStatusBarBehavior::InterfaceStatusBarBehavior(Interface* const inter) :
	m_owner(inter)
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



const InterfaceBehaviorType InterfaceStatusBarBehavior::GetType() const noexcept
{
	return InterfaceBehaviorType::INTERFACR_BEHAVIOR_TYPE_STATUSBAR;
}
