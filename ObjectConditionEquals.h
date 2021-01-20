#pragma once
#include "ICondition.h"
#include "IObjectVariable.h"

class ObjectConditionEquals :
	public ICondition
{
	class IObjectVariable* m_A;
	class IObjectVariable* m_B;

public:
	ObjectConditionEquals(class IObjectVariable* const A, class IObjectVariable* const B);
	bool CheckCondition() override;
};

