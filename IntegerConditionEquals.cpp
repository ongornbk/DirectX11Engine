#include "IntegerConditionEquals.h"

IntegerConditionEquals::IntegerConditionEquals(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

bool IntegerConditionEquals::CheckCondition()
{
	return (m_A->get() == m_B->get());
}
