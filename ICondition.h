#pragma once
#include <typeinfo>

#include <modern__.h>

class ICondition
{
protected:
	//std::type_info m_id;
public:
	virtual ~ICondition();
	virtual modern_Boolean CheckCondition() = 0;
};
