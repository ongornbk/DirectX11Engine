#pragma once
#include "gdef.h"

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

	virtual const ParameterType get_type() const noexcept = 0;
};

