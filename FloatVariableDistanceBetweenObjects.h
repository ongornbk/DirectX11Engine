#pragma once
#include "IFloatVariable.h"
#include "modern/modern_handle.h"

class FloatVariableDistanceBetweenObjects :
	public IFloatVariable
{
	class modern_handle object_A;
	class modern_handle object_B;
public:
	FloatVariableDistanceBetweenObjects(class GameObject* const A,class GameObject* const B);
	const float get() override;
};



