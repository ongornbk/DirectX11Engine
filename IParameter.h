#pragma once
#include "gdef.h"
#include "modern/modern_def.h"

enum class ParameterType
{
	POINTER,
	SPOINTER,
	BASIC
};

class IParameter
{
protected:


public:

	virtual const ParameterType get_type() const modern_except_state = 0;
};

