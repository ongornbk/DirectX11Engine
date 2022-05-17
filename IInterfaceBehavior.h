#pragma once
#include "InterfaceBehaviorType.h"

class IInterfaceBehavior
{
public:
	virtual void OnHover() = 0;
	virtual void OnClick() = 0;
	virtual const enum class InterfaceBehaviorType GetType() const noexcept = 0;

	virtual ~IInterfaceBehavior();
};

