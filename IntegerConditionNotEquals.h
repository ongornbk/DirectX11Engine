#pragma once
#include "ICondition.h"
#include "IIntegerVariable.h"

class IntegerConditionNotEquals :
	public ICondition
{
	class IIntegerVariable* m_A;
	class IIntegerVariable* m_B;

public:
	IntegerConditionNotEquals(class IIntegerVariable* const A, class IIntegerVariable* const B);
	bool CheckCondition() override;
};


