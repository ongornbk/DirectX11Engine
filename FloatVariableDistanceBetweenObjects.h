#pragma once
#include "IFloatVariable.h"
#include "modern/modern_handle.h"

class FloatVariableDistanceBetweenObjects :
	public IFloatVariable
{
	class modern_handle object_A;
	class modern_handle object_B;
public:
	FloatVariableDistanceBetweenObjects(class EObject* const A,class EObject* const B);
	const float get() override;
};



