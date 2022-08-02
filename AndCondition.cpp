#include "AndCondition.h"
#include <cassert>

AndCondition::AndCondition(ICondition* const __A, ICondition* const __B)
{
	assert(A && B);
	A = __A;
	B = __B;
}

AndCondition::~AndCondition()
{
	if (A)
	{
		delete A;
		A = nullptr;
	}
	if (B)
	{
		delete B;
		B = nullptr;
	}
}

modern_Boolean AndCondition::CheckCondition()
{
	return (A->CheckCondition() && B->CheckCondition());
}
