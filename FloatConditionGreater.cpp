#include "FloatConditionGreater.h"
#include <cassert>

FloatConditionGreater::FloatConditionGreater(IFloatVariable* const A, IFloatVariable* const B) : m_A(A), m_B(B)
{

}

bool FloatConditionGreater::CheckCondition()
{
	return (m_A->get() > m_B->get());
}
