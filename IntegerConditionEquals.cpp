#include "IntegerConditionEquals.h"

IntegerConditionEquals::IntegerConditionEquals(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

modern_Boolean IntegerConditionEquals::CheckCondition()
{
	return (m_A->get() == m_B->get());
}
