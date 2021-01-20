#pragma once
#include "IAction.h"
#include "ICondition.h"
#include "IActionSplitArrayBehavior.h"

class ActionIfThenElse :
	public IAction, public IActionSplitArrayBehavior
{
	class ICondition* m_if;
	class IAction* m_then;
	class IAction* m_else;
	ActionIfThenElse() = delete;
public:
	ActionIfThenElse(class ICondition* const __condition,class IAction* const __then,class IAction* const __else);
	~ActionIfThenElse();

	void execute() override;
	class IAction* const GetThen();

	const enum class ActionBehavior execute_in_array() override;
	const enum class ActionType GetType() override;
};

