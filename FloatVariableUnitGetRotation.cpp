#include "FloatVariableUnitGetRotation.h"
#include "Unit.h"
#include <cassert>

FloatVariableUnitGetRotation::FloatVariableUnitGetRotation(Unit* const __unit)
{
	unit = __unit;
}

const float FloatVariableUnitGetRotation::get()
{
	assert(unit);
	if (unit)
	{
		return unit->GetRotation();
	}
	return 0.f;
}
