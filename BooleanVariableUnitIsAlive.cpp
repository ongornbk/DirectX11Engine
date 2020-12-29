#include "BooleanVariableUnitIsAlive.h"
#include "Unit.h"
#include <cassert>

BooleanVariableUnitIsAlive::BooleanVariableUnitIsAlive(Unit* const __unit) : unit(__unit)
{
}

const bool BooleanVariableUnitIsAlive::get()
{
	assert(unit);
	if (unit)
	{
		return unit->IsAlive();
	}
	return false;
}
