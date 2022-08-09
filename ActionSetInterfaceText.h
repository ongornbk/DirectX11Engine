#pragma once
#include "IAction.h"
#include "Interface.h"
class ActionSetInterfaceText :
    public IAction
{
    string m_text;
    class Interface* m_interface;
    float m_size;

    ActionSetInterfaceText() = delete;

public:

    ActionSetInterfaceText(class Interface* const inter,string text,const float size);
    ~ActionSetInterfaceText();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};

