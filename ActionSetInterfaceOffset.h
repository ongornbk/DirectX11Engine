#pragma once
#include "IAction.h"
#include "Interface.h"
#include "modern/modern_guard.h"
#include "modern/modern_handle.h"

class ActionSetInterfaceOffset :
    public IAction
{
    DirectX::XMFLOAT3 m_offset;
    modern_handle m_interface;

    ActionSetInterfaceOffset() = delete;

public:

    ActionSetInterfaceOffset(Interface* const inter, DirectX::XMFLOAT3& offset);
    ActionSetInterfaceOffset(modern_handle& inter, DirectX::XMFLOAT3& offset);
    ~ActionSetInterfaceOffset();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};

