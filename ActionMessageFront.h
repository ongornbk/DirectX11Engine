#pragma once
#include "IAction.h"

class ActionMessageFront :
	public IAction
{
	class GameObject* m_object;

	ActionMessageFront() = delete;

public:

	ActionMessageFront(class GameObject* const object);
	~ActionMessageFront();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

