#pragma once
#include "ICondition.h"

class NorCondition :
	public ICondition
{
	class ICondition* A{};
	class ICondition* B{};
public:
	NorCondition() = delete;
	NorCondition(class ICondition* const __A, class ICondition* const __B);
	~NorCondition();
	modern_Boolean CheckCondition() override;
};



