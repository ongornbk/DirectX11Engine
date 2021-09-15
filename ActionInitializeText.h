#pragma once
#include "IAction.h"
#include "Text.h"

class ActionInitializeText :
    public IAction
{
    Text** m_text;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    Shader* m_shader;
    TextFont* m_font;
    float m_size;

    ActionInitializeText() = delete;

public:

    ActionInitializeText(Text** const text,ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, TextFont* font, float size);
    ~ActionInitializeText();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};
