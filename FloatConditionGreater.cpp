#include "FloatConditionGreater.h"
#include <cassert>

FloatConditionGreater::FloatConditionGreater(IFloatVariable* const A, IFloatVariable* const B)
{
	assert(A && B);
	m_A = A;
	m_B = B;
}

modern_Boolean FloatConditionGreater::CheckCondition()
{
	return (m_A->get() > m_B->get());
}
