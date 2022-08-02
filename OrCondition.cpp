#include "OrCondition.h"
#include <cassert>

OrCondition::OrCondition(ICondition* const __A, ICondition* const __B)// : A(__A), B(__B)
{
	assert(__A && __B);
	A = __A;
	B = __B;
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

modern_Boolean OrCondition::CheckCondition()
{
	return false;// (A->CheckCondition() || B->CheckCondition());
}
