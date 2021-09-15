#pragma once
#include "IAction.h"
#include "Interface.h"
class ActionSetInterfaceText :
    public IAction
{
    string m_text;
    Interface* m_interface;

    ActionSetInterfaceText() = delete;

public:

    ActionSetInterfaceText(class Interface* const inter,string text);
    ~ActionSetInterfaceText();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};

