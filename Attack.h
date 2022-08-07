#pragma once
#include "AttackType.h"

struct Attack
{
	Attack(void);
	Attack(const float _range);


	float range;
	mutable bool active;
	mutable bool delay;
	float m_attackDelay;

	enum class AttackType m_atype;
};