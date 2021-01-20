#pragma once
#include "IFloatVariable.h"
class Unit;

class FloatVariableUnitGetRotation :
	public IFloatVariable
{
	class Unit* unit;
public:
	FloatVariableUnitGetRotation(class Unit* const __unit);
	const float get() override;
};


