#include "NorCondition.h"
#include <cassert>

NorCondition::NorCondition(ICondition* const __A, ICondition* const __B) : A(__A), B(__B)
{
	assert(A && B);
}

NorCondition::~NorCondition()
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

bool NorCondition::CheckCondition()
{
	return !(A->CheckCondition() || B->CheckCondition());
}
