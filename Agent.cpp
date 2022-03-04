#include "Agent.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"

Agent::Agent()
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_boundingSphere.Radius = 0.0f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = false;
}

Agent::~Agent()
{
}

void Agent::Initialize(const XMFLOAT3 position)
{
    m_boundingSphere.Center = position;
}

void _fastcall Agent::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void _fastcall Agent::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void Agent::Update(float dt)
{
}

void Agent::SetZ(float z)
{
}

void Agent::Release()
{
    m_flags.m_hide = true;
}

int32 Agent::isReleased() const noexcept
{
    return m_flags.m_hide;
}

void Agent::Intersect(EObject* const other)
{

}

const RenderLayerType Agent::GetLayerType() const noexcept
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void Agent::Remove()
{
    class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
    action->push(new ActionRemoveObject(this));
    Timer::CreateInstantTimer(action);
}

void Agent::SetVector(const DirectX::XMFLOAT3& vec) noexcept
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 Agent::GetVector() noexcept
{
    return DirectX::XMFLOAT3();
}
