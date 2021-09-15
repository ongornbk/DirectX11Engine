#include "ActionInitializeText.h"

ActionInitializeText::ActionInitializeText(Text** const text, ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, TextFont* font, float size) :
    m_text(text),
    m_device(device),
    m_deviceContext(deviceContext),
    m_shader(shader),
    m_font(font),
    m_size(size)
{
}

ActionInitializeText::~ActionInitializeText()
{
}

void ActionInitializeText::execute()
{
    if (m_device && m_deviceContext && m_shader && m_font)
    {
        (*m_text) = new Text();
        (*m_text)->Initialize(m_device, m_deviceContext, m_shader, m_font, m_size);
        (*m_text)->SetPosition({ 0.f,0.f,0.f });
    }
}

const ActionBehavior ActionInitializeText::execute_in_array()
{
    this->execute();
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
