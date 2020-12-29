#pragma once
#include "IBooleanVariable.h"

class Unit;

class BooleanVariableUnitIsDead :
	public IBooleanVariable
{
	class Unit* unit;
public:
	BooleanVariableUnitIsDead(class Unit* const __unit);
	const bool get() override;
};
