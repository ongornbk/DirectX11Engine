#pragma once
#include "IBooleanVariable.h"
#include "Unit.h"

class BooleanVariableUnitIsAlive :
	public IBooleanVariable
{
	class modern_handle unit;
public:
	BooleanVariableUnitIsAlive(class Unit* const __unit);
	BooleanVariableUnitIsAlive(const class modern_handle& __unit);
	const bool get() override;
};


