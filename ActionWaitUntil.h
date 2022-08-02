#pragma once
#include "IAction.h"
#include "ICondition.h"
#include "IActionSplitArrayBehavior.h"
#include "IActionCondition.h"

class ActionWaitUntil : public IAction, public IActionSplitArrayBehavior, public IActionCondition
{
	class ICondition* m_condition{};

	ActionWaitUntil() = delete;

public:

	ActionWaitUntil(class ICondition* const condition);
	~ActionWaitUntil();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;

	const enum class ActionType GetType() override;

	class ICondition* const GetCondition() override;
};

