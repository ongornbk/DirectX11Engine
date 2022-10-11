#pragma once
#include "IAction.h"
#include "Unit.h"

class ActionNotifyBlock :
	public IAction
{
	class modern_handle m_object;
	class modern_handle m_other;

	ActionNotifyBlock() = delete;

public:

	ActionNotifyBlock(class Unit* const object,class GameObject* const other);
	~ActionNotifyBlock();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};