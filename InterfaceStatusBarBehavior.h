#pragma once
#include "IInterfaceBehavior.h"
#include "IBindableBehavior.h"

class InterfaceStatusBarBehavior :
	public IInterfaceBehavior
{
public:
	InterfaceStatusBarBehavior(class Interface* const inter);
	~InterfaceStatusBarBehavior();

	void OnHover() override;
	void OnClick() override;

	void SetStatus(const float status);

	const enum class InterfaceBehaviorType GetType() const noexcept override;

private:
	class Interface* m_owner;
	float            m_status;
};

