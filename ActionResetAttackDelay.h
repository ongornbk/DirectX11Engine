#pragma once
#include "IAction.h"

class ActionResetAttackDelay :
	public IAction
{
	class modern_handle m_object;

	ActionResetAttackDelay() = delete;

public:

	ActionResetAttackDelay(const modern_handle& handle);
	~ActionResetAttackDelay();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};