#pragma once
#include "IFloatVariable.h"
class Unit;

class FloatVariableUnitDistanceFromCamera :
	public IFloatVariable
{
	class Unit* unit;
public:
	FloatVariableUnitDistanceFromCamera(class Unit* const __unit);
	const float get() override;
};



