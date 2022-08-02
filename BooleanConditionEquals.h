#pragma once
#include "ICondition.h"
#include "IBooleanVariable.h"


class BooleanConditionEquals :
	public ICondition
{
	class IBooleanVariable* m_A;
	class IBooleanVariable* m_B;

public:
	BooleanConditionEquals(class IBooleanVariable* const A, class IBooleanVariable* const B);
	modern_Boolean CheckCondition() override;
};

