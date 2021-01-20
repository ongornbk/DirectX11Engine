#pragma once
#include "ICondition.h"
#include "IFloatVariable.h"

class FloatConditionLess :
	public ICondition
{
	class IFloatVariable* m_A;
	class IFloatVariable* m_B;

public:
	FloatConditionLess(class IFloatVariable* const A, class IFloatVariable* const B);
	bool CheckCondition() override;
};




