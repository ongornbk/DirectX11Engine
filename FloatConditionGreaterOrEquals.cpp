#include "FloatConditionGreaterOrEquals.h"
#include <cassert>

FloatConditionGreaterOrEquals::FloatConditionGreaterOrEquals(IFloatVariable* const A, IFloatVariable* const B) : m_A(A), m_B(B)
{

}

modern_Boolean FloatConditionGreaterOrEquals::CheckCondition()
{
	return (m_A->get() >= m_B->get());
}
