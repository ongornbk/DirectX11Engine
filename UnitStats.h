#pragma once
#include <cstdint>

struct UnitStats
{
	UnitStats();
	~UnitStats();

	float    m_health;
	float    m_maxHealth;
	float    m_attackDamage;
	float    m_healthRegeneration;
	float    m_mana;
	float    m_maxMana;
	float    m_manaRegeneration;
	float    m_exp;
	float    m_maxExp;//T
	float    m_expBonus;//T
	uint32_t m_level;//T
};

