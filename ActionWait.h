#pragma once
#include "IAction.h"
#include "ActionExecuteActionArray.h"
#include "IActionSplitArrayBehavior.h"
#include "IActionTimer.h"

class ActionWait :
	public IAction, public IActionSplitArrayBehavior, public IActionTimer
{
	float m_duration;


	ActionWait() = delete;

public:

	ActionWait(float duration);
	~ActionWait();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;

	const enum class ActionType GetType() override;

	const float GetDuration() override;
};

