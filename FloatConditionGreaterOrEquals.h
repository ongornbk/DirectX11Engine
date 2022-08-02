#pragma once
#include "ICondition.h"
#include "IFloatVariable.h"

class FloatConditionGreaterOrEquals :
	public ICondition
{
	class IFloatVariable* m_A;
	class IFloatVariable* m_B;

public:
	FloatConditionGreaterOrEquals(class IFloatVariable* const A, class IFloatVariable* const B);
	modern_Boolean CheckCondition() override;
};


