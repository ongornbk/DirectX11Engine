#include "BooleanVariableUnitIsDead.h"
#include "Unit.h"
#include <cassert>

BooleanVariableUnitIsDead::BooleanVariableUnitIsDead(Unit* const __unit) : unit(__unit)
{
}

const bool BooleanVariableUnitIsDead::get()
{
	assert(unit);
	if (unit)
	{
		return unit->IsDead();
	}
	return false;
}
