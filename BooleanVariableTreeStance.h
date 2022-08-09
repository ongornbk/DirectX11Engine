#pragma once
#include "IBooleanVariable.h"
#include "Tree.h"

class BooleanVariableTreeStance :
	public IBooleanVariable
{
	class modern_handle tree;
public:
	BooleanVariableTreeStance(class Tree* const __tree);
	BooleanVariableTreeStance(const class modern_handle& __tree);
	const bool get() override;
};
