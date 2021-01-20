#pragma once
#include "ICondition.h"
#include "IObjectVariable.h"

class ObjectConditionNotEquals :
	public ICondition
{
	class IObjectVariable* m_A;
	class IObjectVariable* m_B;

public:
	ObjectConditionNotEquals(class IObjectVariable* const A, class IObjectVariable* const B);
	bool CheckCondition() override;
};

