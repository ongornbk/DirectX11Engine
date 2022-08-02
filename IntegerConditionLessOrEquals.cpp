#include "IntegerConditionLessOrEquals.h"

IntegerConditionLessOrEquals::IntegerConditionLessOrEquals(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

modern_Boolean IntegerConditionLessOrEquals::CheckCondition()
{
	return (m_A->get() <= m_B->get());
}
