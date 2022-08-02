#pragma once
#include "IInterfaceBehavior.h"
#include "Interface.h"

class InterfaceButtonBehavior :
	public IInterfaceBehavior
{
public:
	InterfaceButtonBehavior(class Interface* const inter);
	~InterfaceButtonBehavior();

	void OnHover() override;
	void OnClick() override;
	const enum class InterfaceBehaviorType GetType() const modern_except_state override;

	void SetOnClick(std::string click);
private:
	class Interface* m_owner;
	std::string      m_click;
};

