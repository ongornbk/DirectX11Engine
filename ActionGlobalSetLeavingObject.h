#pragma once
#include "IAction.h"
#include "GameObject.h"
#include "Global.h"

class ActionGlobalSetLeavingObject :
	public IAction
{
	volatile class modern_handle m_object;

	ActionGlobalSetLeavingObject() = delete;

public:

	ActionGlobalSetLeavingObject(class modern_handle& object);
	~ActionGlobalSetLeavingObject();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};