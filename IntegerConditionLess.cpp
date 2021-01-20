#include "IntegerConditionLess.h"

IntegerConditionLess::IntegerConditionLess(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

bool IntegerConditionLess::CheckCondition()
{
	return (m_A->get() < m_B->get());
}
