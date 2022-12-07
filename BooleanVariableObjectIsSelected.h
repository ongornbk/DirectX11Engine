#pragma once
#include "IBooleanVariable.h"

#include <modern__.h>

class GameObject;

class BooleanVariableObjectIsSelected :
	public IBooleanVariable
{
	class modern_handle object;
public:
	BooleanVariableObjectIsSelected(class GameObject* const __object);
	const bool get() override;
};

