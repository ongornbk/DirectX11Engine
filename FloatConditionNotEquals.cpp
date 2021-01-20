#include "FloatConditionNotEquals.h"
#include <cassert>

FloatConditionNotEquals::FloatConditionNotEquals(IFloatVariable* const A, IFloatVariable* const B) : m_A(A), m_B(B)
{

}

bool FloatConditionNotEquals::CheckCondition()
{
	return (m_A->get() != m_B->get());
}
