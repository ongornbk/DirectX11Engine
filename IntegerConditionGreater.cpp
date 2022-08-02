#include "IntegerConditionGreater.h"

IntegerConditionGreater::IntegerConditionGreater(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

modern_Boolean IntegerConditionGreater::CheckCondition()
{
	return (m_A->get() > m_B->get());
}
