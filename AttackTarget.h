#pragma once
#include "RenderContainer.h"

struct AttackTarget
{
	enum ATType
	{
		UNIT
	} m_ATtype;

	AttackTarget(class EObject* const rc, const enum AttackTarget::ATType type);

	

	EObject* ATtarget;
};

