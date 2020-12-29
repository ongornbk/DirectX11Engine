#include "BooleanVariableUnitIsAttacking.h"
#include "Unit.h"
#include <cassert>

BooleanVariableUnitIsAttacking::BooleanVariableUnitIsAttacking(Unit* const __unit) : unit(__unit)
{
}

const bool BooleanVariableUnitIsAttacking::get()
{
	assert(unit);
	if (unit)
	{
		return unit->IsAttacking();
	}
	return false;
}
