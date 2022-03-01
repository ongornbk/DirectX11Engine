#include "ActionInitializeInterface.h"

ActionInitializeInterface::ActionInitializeInterface(
    modern_handle& inter, ID3D11Device* const device,
    ID3D11DeviceContext* const deviceContext,
    Shader* const shader,
    modern_string& paths,
    const DirectX::XMFLOAT3& position,
    const DirectX::XMFLOAT2& size
) : m_device(device), m_deviceContext(deviceContext), m_shader(shader), m_position(position), m_size(size), m_paths(paths)
{
    m_interface.make_handle((new Interface())->GetHandle());
    inter.make_handle(m_interface);
}

ActionInitializeInterface::~ActionInitializeInterface()
{
}

void ActionInitializeInterface::execute()
{
    if (m_device && m_deviceContext && m_shader)
    {
        //m_text.make_handle(new Text());

        class Interface* const A = (class Interface*)m_interface.get();
        if (A)
        {
            modern_guard g(A);
            A->Initialize(m_device, m_deviceContext, m_shader, m_paths.c_wstr(),m_position, m_size.x,m_size.y);
            //A->SetPosition(DirectX::XMFLOAT3{ 0.f,0.f,0.f });

        }
    }
}

const ActionBehavior ActionInitializeInterface::execute_in_array()
{
    this->execute();
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
