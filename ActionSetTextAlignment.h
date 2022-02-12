#pragma once
#include "IAction.h"

#include "modern/modern_guard.h"
#include "modern/modern_handle.h"

enum class TextAlignment;

class ActionSetTextAlignment :
    public IAction
{
    modern_handle m_text;
    enum class TextAlignment m_align;

    ActionSetTextAlignment() = delete;

public:

    ActionSetTextAlignment(class modern_handle& text,const enum class TextAlignment alignment);
    ~ActionSetTextAlignment();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};

