#pragma once
#include "IInterfaceBehavior.h"
#include "Interface.h"

class InterfaceCheckboxBehavior :
	public IInterfaceBehavior
{
public:
	InterfaceCheckboxBehavior(class Interface* const inter);
	~InterfaceCheckboxBehavior();

	void OnHover() override;
	void OnClick() override;
	const enum class InterfaceBehaviorType GetType() const noexcept override;

private:
	class Interface* m_owner;
	bool             m_checked;
};

