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
#include "BooleanVariableObjectIsSelected.h"
#include "BooleanVariableIsKeyDown.h"
#include "BooleanOperatorType.h"
#pragma endregion
#pragma region Float
#include "FloatConditionEquals.h"
#include "FloatConditionGreater.h"
#include "FloatConditionGreaterOrEquals.h"
#include "FloatConditionLess.h"
#include "FloatConditionLessOrEquals.h"
#include "FloatConditionNotEquals.h"
#include "ConstFloatVariable.h"
#include "FloatVariableUnitGetRotation.h"
#include "FloatVariableUnitDistanceFromCamera.h"
#include "FloatVariableDistanceBetweenObjects.h"
#include "FloatOperatorType.h"
#pragma endregion
#pragma region Integer
#include "IntegerConditionEquals.h"
#include "IntegerConditionGreater.h"
#include "IntegerConditionGreaterOrEquals.h"
#include "IntegerConditionLess.h"
#include "IntegerConditionLessOrEquals.h"
#include "IntegerConditionNotEquals.h"
#include "ConstIntegerVariable.h"
#include "IntegerOperatorType.h"
#pragma endregion
#pragma region Object
#include "ConstObjectVariable.h"
#include "ObjectOperatorType.h"
#include "ObjectConditionEquals.h"
#include "ObjectConditionNotEquals.h"
#pragma endregion
#pragma region Others
#include "AndCondition.h"
#include "OrCondition.h"
#pragma endregion

namespace ConditionFactory
{
	class ICondition* const CreateBooleanCondition(class IBooleanVariable* const A, class IBooleanVariable* const B, const enum class BooleanOperatorType operator_type) noexcept;
	class ICondition* const CreateFloatCondition(class IFloatVariable* const A, class IFloatVariable* const B, const enum class FloatOperatorType operator_type) noexcept;
	class ICondition* const CreateIntegerCondition(class IIntegerVariable* const A, class IIntegerVariable* const B, const enum class IntegerOperatorType operator_type) noexcept;
	class ICondition* const CreateObjectCondition(class IObjectVariable* const A, class IObjectVariable* const B, const enum class ObjectOperatorType operator_type) noexcept;
	class ICondition* const CreateAndCondition(class ICondition* const A, class ICondition* const B) noexcept;
	class ICondition* const CreateOrCondition(class ICondition* const A, class ICondition* const B) noexcept;
}