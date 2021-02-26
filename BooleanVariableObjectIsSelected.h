#pragma once
#include "IBooleanVariable.h"

class EObject;

class BooleanVariableObjectIsSelected :
	public IBooleanVariable
{
	class EObject* object;
public:
	BooleanVariableObjectIsSelected(class EObject* const __object);
	const bool get() override;
};

