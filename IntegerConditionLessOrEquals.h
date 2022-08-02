#pragma once
#include "ICondition.h"
#include "IIntegerVariable.h"

class IntegerConditionLessOrEquals :
	public ICondition
{
	class IIntegerVariable* m_A;
	class IIntegerVariable* m_B;

public:
	IntegerConditionLessOrEquals(class IIntegerVariable* const A, class IIntegerVariable* const B);
	modern_Boolean CheckCondition() override;
};
