#include "BooleanConditionEquals.h"
#include <cassert>

BooleanConditionEquals::BooleanConditionEquals(IBooleanVariable* const A, IBooleanVariable* const B) : m_A(A), m_B(B)
{
	assert(A && B);
}

bool BooleanConditionEquals::CheckCondition()
{
	return (m_A->get() == m_B->get());
}
