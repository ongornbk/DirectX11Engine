#include "IntegerConditionGreater.h"

IntegerConditionGreater::IntegerConditionGreater(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

bool IntegerConditionGreater::CheckCondition()
{
	return (m_A->get() > m_B->get());
}
