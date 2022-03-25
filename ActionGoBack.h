#pragma once
#include "IAction.h"
#include "Unit.h"

class ActionGoBack :
	public IAction
{
	class modern_handle m_object;

	ActionGoBack() = delete;

public:

	ActionGoBack(class Unit* const object);
	~ActionGoBack();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};