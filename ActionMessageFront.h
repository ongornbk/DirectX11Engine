#pragma once
#include "IAction.h"

class ActionMessageFront :
	public IAction
{
	class EObject* m_object;

	ActionMessageFront() = delete;

public:

	ActionMessageFront(class EObject* const object);
	~ActionMessageFront();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

