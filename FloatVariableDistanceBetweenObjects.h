#pragma once
#include "IFloatVariable.h"

class FloatVariableDistanceBetweenObjects :
	public IFloatVariable
{
	class EObject* object_A;
	class EObject* object_B;
public:
	FloatVariableDistanceBetweenObjects(class EObject* const A,class EObject* const B);
	const float get() override;
};



