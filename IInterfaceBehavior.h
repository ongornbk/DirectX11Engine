#pragma once
#include "InterfaceBehaviorType.h"

#include <modern__.h>

class IInterfaceBehavior
{
public:
	virtual void OnHover() = 0;
	virtual void OnClick() = 0;
	virtual const enum class InterfaceBehaviorType GetType() const modern_except_state = 0;

	virtual ~IInterfaceBehavior();
};

