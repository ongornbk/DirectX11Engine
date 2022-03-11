#pragma once
#include "IAction.h"
#include "Tree.h"

class ActionTreeSetStance :
	public IAction
{
	class modern_handle      m_tree;
	modern_Boolean           m_stance;

	ActionTreeSetStance() = delete;

public:

	ActionTreeSetStance(class Tree* const object,const modern_Boolean stance);
	~ActionTreeSetStance();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};


