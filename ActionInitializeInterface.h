#pragma once
#include "Interface.h"
#include "IAction.h"

class ActionInitializeInterface :
    public IAction
{
    class modern_handle m_interface;
    struct ID3D11Device* m_device;
    struct ID3D11DeviceContext* m_deviceContext;
    class Shader* m_interfaceShader;
    class Shader* m_textShader;
    class modern_string m_paths;
    struct DirectX::XMFLOAT3 m_position;
    struct DirectX::XMFLOAT2 m_size;
    enum class ObjectAnchorType m_anchor;

    ActionInitializeInterface() = delete;

public:

    ActionInitializeInterface(
              class  modern_handle&             inter,
              struct ID3D11Device*        const device,
              struct ID3D11DeviceContext* const deviceContext,
              class  Shader*              const interface_shader,
              class Shader* const text_shader,
              class  modern_string&             paths,
        const struct DirectX::XMFLOAT3&         position,
        const struct DirectX::XMFLOAT2&         size,
        const enum class ObjectAnchorType       anchor
    );
    ~ActionInitializeInterface();

    void execute() override;
    const enum class ActionBehavior execute_in_array() override;
};