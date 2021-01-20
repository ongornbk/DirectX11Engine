#include "FloatConditionLess.h"
#include <cassert>

FloatConditionLess::FloatConditionLess(IFloatVariable* const A, IFloatVariable* const B) : m_A(A), m_B(B)
{

}

bool FloatConditionLess::CheckCondition()
{
	return (m_A->get() < m_B->get());
}
