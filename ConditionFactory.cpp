#include "ConditionFactory.h"

ICondition* const ConditionFactory::CreateBooleanCondition(IBooleanVariable* const A, IBooleanVariable* const B, const BooleanOperatorType operator_type) noexcept
{
	if (operator_type == BooleanOperatorType::BOOLEAN_OPERATOR_TYPE_EQUALS)
	{
		return new BooleanConditionEquals(A,B);
	}
	else
	{
		return new BooleanConditionNotEquals(A, B);
	}
}
