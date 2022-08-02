#pragma once
#include "ICondition.h"
#include "IIntegerVariable.h"

class IntegerConditionEquals :
	public ICondition
{
	class IIntegerVariable* m_A;
	class IIntegerVariable* m_B;

public:
	IntegerConditionEquals(class IIntegerVariable* const A, class IIntegerVariable* const B);
	modern_Boolean CheckCondition() override;
};
