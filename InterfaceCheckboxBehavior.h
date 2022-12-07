#pragma once
#include "IInterfaceBehavior.h"
#include "IBindableBehavior.h"
#include "Interface.h"

class InterfaceCheckboxBehavior :
	public IInterfaceBehavior,
	public IBindableBehavior
{
public:
	InterfaceCheckboxBehavior(class Interface* const inter);
	~InterfaceCheckboxBehavior();

	void OnHover() override;
	void OnClick() override;

	void Bind(const modern_cstring& option) override;

	const enum class InterfaceBehaviorType GetType() const modern_except_state override;

private:
	class Interface* m_owner;
	modern_Boolean   m_checked;
};

