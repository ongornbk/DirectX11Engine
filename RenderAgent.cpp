#include "RenderAgent.h"

RenderAgent::RenderAgent()
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_boundingSphere.Radius = 0.0f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = true;

    m_type = EObjectType::OBJECT_TYPE_RENDER_AGENT;

    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DISABLED;
}

RenderAgent::~RenderAgent()
{
}

void RenderAgent::Initialize(Region* const region)
{

    m_boundingSphere.Center = region->GetPosition();
    m_parent.make_handle(region->GetHandle());

}

void _fastcall RenderAgent::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
        class Region* const collline = (class Region* const)m_parent.get();
        collline->Render(deviceContext, viewMatrix, projectionMatrix, shader);
}

void _fastcall RenderAgent::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void RenderAgent::Update(float dt)
{
        class Region* const collline = (class Region* const)m_parent.get();
        collline->Update(dt);
}

void RenderAgent::SetZ(float z)
{
}

void RenderAgent::Release()
{
}

int32 RenderAgent::isReleased() const modern_except_state
{
    return int32();
}

void RenderAgent::Intersect(EObject* const other)
{
}

const RenderLayerType RenderAgent::GetLayerType() const modern_except_state
{
    //return RenderLayerType::ENUM_OBJECT_TYPE;
    interface RenderAgentParent* const collline = (interface RenderAgentParent* const)m_parent.get();
        return collline->GetRenderLayer();
}

void RenderAgent::Remove()
{
    safe_remove();
}

void RenderAgent::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 RenderAgent::GetVector() modern_except_state
{
    return m_boundingSphere.Center;
}
