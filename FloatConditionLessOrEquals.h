#pragma once
#include "ICondition.h"
#include "IFloatVariable.h"

class FloatConditionLessOrEquals :
	public ICondition
{
	class IFloatVariable* m_A;
	class IFloatVariable* m_B;

public:
	FloatConditionLessOrEquals(class IFloatVariable* const A, class IFloatVariable* const B);
	modern_Boolean CheckCondition() override;
};



