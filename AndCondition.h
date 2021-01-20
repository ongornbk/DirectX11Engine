#pragma once
#include "ICondition.h"
class AndCondition :
	public ICondition
{
	class ICondition* A{};
	class ICondition* B{};
public:
	AndCondition() = delete;
	AndCondition(class ICondition* const __A, class ICondition* const __B);
	~AndCondition();
	bool CheckCondition() override;
};

