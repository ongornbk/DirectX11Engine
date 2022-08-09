#include "BooleanVariableUnitIsAlive.h"
#include "Unit.h"
#include <cassert>

BooleanVariableUnitIsAlive::BooleanVariableUnitIsAlive(class Unit* const __unit)
{
	if(__unit)
	unit.make_handle(__unit->GetHandle());
}

BooleanVariableUnitIsAlive::BooleanVariableUnitIsAlive(const class modern_handle& __unit)
{
	unit.make_handle(__unit);
}

const bool BooleanVariableUnitIsAlive::get()
{
	class Unit* const unitt = (class Unit* const)(unit.get());
	if (unitt)
	{
		return unitt->IsAlive();
	}
	return false;
}
