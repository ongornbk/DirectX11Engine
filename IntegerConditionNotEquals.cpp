#include "IntegerConditionNotEquals.h"

IntegerConditionNotEquals::IntegerConditionNotEquals(IIntegerVariable* const A, IIntegerVariable* const B) : m_A(A), m_B(B)
{
}

modern_Boolean IntegerConditionNotEquals::CheckCondition()
{
	return (m_A->get() != m_B->get());
}
