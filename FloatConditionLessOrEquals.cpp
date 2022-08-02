#include "FloatConditionLessOrEquals.h"
#include <cassert>

FloatConditionLessOrEquals::FloatConditionLessOrEquals(IFloatVariable* const A, IFloatVariable* const B) : m_A(A), m_B(B)
{

}

modern_Boolean FloatConditionLessOrEquals::CheckCondition()
{
	return (m_A->get() <= m_B->get());
}
