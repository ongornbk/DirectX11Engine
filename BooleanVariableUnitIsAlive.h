#pragma once
#include "IBooleanVariable.h"
class Unit;

class BooleanVariableUnitIsAlive :
	public IBooleanVariable
{
	class Unit* unit;
public:
	BooleanVariableUnitIsAlive(class Unit* const __unit);
	const bool get() override;
};


