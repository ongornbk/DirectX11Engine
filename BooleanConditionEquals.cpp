#include "BooleanConditionEquals.h"
#include <cassert>

BooleanConditionEquals::BooleanConditionEquals(IBooleanVariable* const A, IBooleanVariable* const B)
{
	assert(A && B);
	m_A = A;
	m_B = B;
}

modern_Boolean BooleanConditionEquals::CheckCondition()
{
	return (m_A->get() == m_B->get());
}
