#pragma once
#include "gdef.h"

#include <modern__.h>

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

	virtual const enum class ParameterType get_type() const modern_except_state = 0;
};

