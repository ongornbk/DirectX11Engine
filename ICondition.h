#pragma once
#include <typeinfo>
#include "modern/modern_def.h"

class ICondition
{
protected:
	//std::type_info m_id;
public:
	virtual ~ICondition();
	virtual modern_Boolean CheckCondition() = 0;
};
