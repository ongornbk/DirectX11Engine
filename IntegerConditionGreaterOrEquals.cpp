#include "IntegerConditionGreaterOrEquals.h"

IntegerConditionGreaterOrEquals::IntegerConditionGreaterOrEquals(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

bool IntegerConditionGreaterOrEquals::CheckCondition()
{
	return (m_A->get() >= m_B->get());
}