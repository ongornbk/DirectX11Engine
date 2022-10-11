#pragma once
#include "IBooleanVariable.h"
#include "modern/modern_handle.h"
#include "modern/modern_guard.h"

class GameObject;

class BooleanVariableObjectIsSelected :
	public IBooleanVariable
{
	class modern_handle object;
public:
	BooleanVariableObjectIsSelected(class GameObject* const __object);
	const bool get() override;
};

