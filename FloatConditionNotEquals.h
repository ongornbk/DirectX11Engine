#pragma once
#include "ICondition.h"
#include "IFloatVariable.h"

class FloatConditionNotEquals :
	public ICondition
{
	class IFloatVariable* m_A;
	class IFloatVariable* m_B;

public:
	FloatConditionNotEquals(class IFloatVariable* const A, class IFloatVariable* const B);
	bool CheckCondition() override;
};



