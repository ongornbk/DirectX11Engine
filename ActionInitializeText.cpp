#include "ActionInitializeText.h"

ActionInitializeText::ActionInitializeText(class modern_handle& text, ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, TextFont* font, float size) :
    m_device(device),
    m_deviceContext(deviceContext),
    m_shader(shader),
    m_font(font),
    m_size(size)
{
    m_text.make_handle((new Text())->GetHandle());
    text.make_handle(m_text);
}

ActionInitializeText::~ActionInitializeText()
{
}

void ActionInitializeText::execute()
{
    if (m_device && m_deviceContext && m_shader && m_font)
    {
        //m_text.make_handle(new Text());

        class Text* const A = (class Text*)m_text.get();
        if (A)
        {
            modern_guard g(A);
            A->Initialize(m_device, m_deviceContext, m_shader, m_font, m_size);
            A->SetPosition({ 0.f,0.f,0.f });

        }
    }
    
}

const ActionBehavior ActionInitializeText::execute_in_array()
{
    this->execute();
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
