#pragma once
#include "IAction.h"
#include "Text.h"
#include "modern/modern_guard.h"
#include "modern/modern_handle.h"

class ActionInitializeText :
    public IAction
{
    modern_handle m_text;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    Shader* m_shader;
    TextFont* m_font;
    float m_size;

    ActionInitializeText() = delete;

public:

    ActionInitializeText(class modern_handle& text,ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, TextFont* font, float size);
    ~ActionInitializeText();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};
