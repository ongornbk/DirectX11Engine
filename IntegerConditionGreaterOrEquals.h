#pragma once
#include "ICondition.h"
#include "IIntegerVariable.h"

class IntegerConditionGreaterOrEquals :
	public ICondition
{
	class IIntegerVariable* m_A;
	class IIntegerVariable* m_B;

public:
	IntegerConditionGreaterOrEquals(class IIntegerVariable* const A, class IIntegerVariable* const B);
	bool CheckCondition() override;
};
