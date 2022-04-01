#include "UnitStats.h"

UnitStats::UnitStats()
{
	m_health = 100.f;
	m_mana = 100.f;
	m_maxHealth = 100.f;
	m_maxMana = 100.f;
	m_healthRegeneration = 1.f;
	m_manaRegeneration = 1.f;
	m_attackDamage = 10.f;
	m_exp = 0.f;
	m_maxExp = 100.f;
	m_expBonus = 10.f;
	m_level = 1;
}

UnitStats::~UnitStats()
{
}
