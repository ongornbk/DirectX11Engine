#pragma once
#include "IAction.h"
#include "Interface.h"
#include "modern/modern_guard.h"
#include "modern/modern_handle.h"

class ActionShowInterface :
    public IAction
{
    modern_handle  m_interface;
    modern_Boolean m_value;

    ActionShowInterface() = delete;

public:

    ActionShowInterface(class Interface* const inter, const modern_Boolean value = modern_true);
    ActionShowInterface(const class modern_handle& inter, const modern_Boolean value = modern_true);
    ~ActionShowInterface();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};

