#pragma once
#include "Attack.h"

__interface IAttackOwner
{
	virtual struct Attack& GetAttack() = 0;
};