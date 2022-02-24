#pragma once
#include "modern/modern_handle.h"
#include "modern/modern_string.h"
#include "Interface.h"
#include "IAction.h"

class ActionInitializeInterface :
    public IAction
{
    modern_handle m_interface;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    Shader* m_shader;
    modern_string m_paths;
    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT2 m_size;

    ActionInitializeInterface() = delete;

public:

    ActionInitializeInterface(
              class  modern_handle&             inter,
              struct ID3D11Device*        const device,
              struct ID3D11DeviceContext* const deviceContext,
              class  Shader*              const shader,
              class  modern_string&             paths,
        const struct DirectX::XMFLOAT3&         position,
        const struct DirectX::XMFLOAT2&         size
    );
    ~ActionInitializeInterface();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};