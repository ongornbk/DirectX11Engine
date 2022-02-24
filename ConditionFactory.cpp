#include "ConditionFactory.h"
#include <cassert>

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

ICondition* const ConditionFactory::CreateFloatCondition(IFloatVariable* const A, IFloatVariable* const B, const FloatOperatorType operator_type) noexcept
{
	switch (operator_type)
	{
	case FloatOperatorType::FLOAT_OPERATOR_TYPE_EQUALS:
	{
		return new FloatConditionEquals(A, B);
	}
	break;
	case FloatOperatorType::FLOAT_OPERATOR_TYPE_GREATER:
	{
		return new FloatConditionGreater(A, B);
	}
	break;
	case FloatOperatorType::FLOAT_OPERATOR_TYPE_GREATER_OR_EQUALS:
	{
		return new FloatConditionGreaterOrEquals(A, B);
	}
	break;
	case FloatOperatorType::FLOAT_OPERATOR_TYPE_LESS:
	{
		return new FloatConditionLess(A, B);
	}
	break;
	case FloatOperatorType::FLOAT_OPERATOR_TYPE_LESS_OR_EQUALS:
	{
		return new FloatConditionLessOrEquals(A, B);
	}
	break;
	case FloatOperatorType::FLOAT_OPERATOR_TYPE_NOT_EQUALS:
	{
		return new FloatConditionNotEquals(A, B);
	}
	break;
	}

	assert(0);
	return nullptr;
}

ICondition* const ConditionFactory::CreateIntegerCondition(IIntegerVariable* const A, IIntegerVariable* const B, const IntegerOperatorType operator_type) noexcept
{
	switch (operator_type)
	{
	case IntegerOperatorType::INTEGER_OPERATOR_TYPE_EQUALS:
	{
		return new IntegerConditionEquals(A, B);
	}
	break;
	case IntegerOperatorType::INTEGER_OPERATOR_TYPE_GREATER:
	{
		return new IntegerConditionGreater(A, B);
	}
	break;
	case IntegerOperatorType::INTEGER_OPERATOR_TYPE_GREATER_OR_EQUALS:
	{
		return new IntegerConditionGreaterOrEquals(A, B);
	}
	break;
	case IntegerOperatorType::INTEGER_OPERATOR_TYPE_LESS:
	{
		return new IntegerConditionLess(A, B);
	}
	break;
	case IntegerOperatorType::INTEGER_OPERATOR_TYPE_LESS_OR_EQUALS:
	{
		return new IntegerConditionLessOrEquals(A, B);
	}
	break;
	case IntegerOperatorType::INTEGER_OPERATOR_TYPE_NOT_EQUALS:
	{
		return new IntegerConditionNotEquals(A, B);
	}
	break;
	}

	assert(0);
	return nullptr;
}

class ICondition* const ConditionFactory::CreateObjectCondition(IObjectVariable* const A, IObjectVariable* const B, const ObjectOperatorType operator_type) noexcept
{
	if (operator_type == ObjectOperatorType::OBJECT_OPERATOR_TYPE_EQUALS)
	{
		return new ObjectConditionEquals(A, B);
	}
	else
	{
		return new ObjectConditionNotEquals(A, B);
	}
}

ICondition* const ConditionFactory::CreateAndCondition(ICondition* const A, ICondition* const B) noexcept
{
	return new AndCondition(A, B);
}

ICondition* const ConditionFactory::CreateOrCondition(ICondition* const A, ICondition* const B) noexcept
{
	return new OrCondition(A, B);
}

ICondition* const ConditionFactory::CreateNorCondition(ICondition* const A, ICondition* const B) noexcept
{
	return new NorCondition(A, B);
}
