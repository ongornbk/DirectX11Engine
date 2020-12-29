#pragma once
#include "IBooleanVariable.h"
class Unit;

class BooleanVariableUnitIsAttacking :
	public IBooleanVariable
{
	class Unit* unit;
public:
	BooleanVariableUnitIsAttacking(class Unit* const __unit);
	const bool get() override;
};

