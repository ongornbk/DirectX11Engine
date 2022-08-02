#pragma once
#include "ICondition.h"
#include "IIntegerVariable.h"

class IntegerConditionGreater :
	public ICondition
{
	class IIntegerVariable* m_A;
	class IIntegerVariable* m_B;

public:
	IntegerConditionGreater(class IIntegerVariable* const A, class IIntegerVariable* const B);
	modern_Boolean CheckCondition() override;
};
