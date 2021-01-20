#include "OrCondition.h"
#include <cassert>

OrCondition::OrCondition(ICondition* const __A, ICondition* const __B) : A(__A), B(__B)
{
	assert(A && B);
}

OrCondition::~OrCondition()
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

bool OrCondition::CheckCondition()
{
	return (A->CheckCondition() || B->CheckCondition());
}
