#pragma once
#include "ICondition.h"

class OrCondition :
	public ICondition
{
	class ICondition* A{};
	class ICondition* B{};
public:
	OrCondition() = delete;
	OrCondition(class ICondition* const __A, class ICondition* const __B);
	~OrCondition();
	bool CheckCondition() override;
};



