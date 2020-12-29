#pragma once
#pragma region Boolean
#include "BooleanConditionEquals.h"
#include "BooleanConditionNotEquals.h"
#include "ConstBooleanVariable.h"
#include "ConstBooleanVariableFalse.h"
#include "ConstBooleanVariableTrue.h"
#include "BooleanVariableUnitIsDead.h"
#include "BooleanVariableUnitIsAlive.h"
#include "BooleanVariableUnitIsAttacking.h"
#include "BooleanOperatorType.h"
#pragma endregion
#pragma region Float
#include "FloatOperatorType.h"
#pragma endregion

namespace ConditionFactory
{
	class ICondition* const CreateBooleanCondition(class IBooleanVariable* const A, class IBooleanVariable* const B, const enum class BooleanOperatorType operator_type) noexcept;
}