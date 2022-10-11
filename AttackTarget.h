#pragma once
#include "GameObject.h"

struct AttackTarget
{
	enum ATType
	{
		UNIT
	} m_ATtype;

	AttackTarget(class GameObject* const rc, const enum AttackTarget::ATType type);

	

	GameObject* ATtarget;
};

