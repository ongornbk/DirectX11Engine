#pragma once
#include "ICondition.h"
#include "IBooleanVariable.h"


class BooleanConditionNotEquals :
	public ICondition
{
	class IBooleanVariable* m_A;
	class IBooleanVariable* m_B;

public:
	BooleanConditionNotEquals(class IBooleanVariable* const A, class IBooleanVariable* const B);
	modern_Boolean CheckCondition() override;
};

