#include "IntegerConditionLessOrEquals.h"

IntegerConditionLessOrEquals::IntegerConditionLessOrEquals(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

bool IntegerConditionLessOrEquals::CheckCondition()
{
	return (m_A->get() <= m_B->get());
}
