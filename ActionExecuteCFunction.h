#pragma once
#include "IAction.h"
#include "CFunctionVoid.h"

class ActionExecuteCFunction :
    public IAction
{
	class ICFunction* m_foo;

	ActionExecuteCFunction() = delete;
public:
	ActionExecuteCFunction(void (*void_f)(void));
	~ActionExecuteCFunction();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};




