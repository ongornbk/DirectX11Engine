#pragma once
#include "modern/modern_exception.h"

class ITask
{
public:
	virtual void execute() = 0;
};

