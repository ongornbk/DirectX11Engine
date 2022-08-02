#include "ObjectConditionEquals.h"

ObjectConditionEquals::ObjectConditionEquals(class IObjectVariable* const A,class IObjectVariable* const B) : m_A(A), m_B(B)
{
	assert(A && B);
}

modern_Boolean ObjectConditionEquals::CheckCondition()
{
	return (m_A->get() == m_B->get());
}
