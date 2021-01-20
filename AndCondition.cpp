#include "AndCondition.h"
#include <cassert>

AndCondition::AndCondition(ICondition* const __A, ICondition* const __B) : A(__A), B(__B)
{
	assert(A && B);
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

bool AndCondition::CheckCondition()
{
	return (A->CheckCondition() && B->CheckCondition());
}
