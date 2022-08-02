#include "Agent.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"

Agent::Agent() : m_intersectStance(AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT)
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_boundingSphere.Radius = 0.0f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = false;

    m_type = EObjectType::OBJECT_TYPE_AGENT;
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
    m_intersectStance = AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT;
}

void Agent::SetZ(float z)
{
}

void Agent::Release()
{
    m_flags.m_hide = true;
}

int32 Agent::isReleased() const modern_except_state
{
    return m_flags.m_hide;
}

void Agent::Intersect(EObject* const other)
{
    if (other == nullptr)
        return;
    if (other == this)
        return;



    switch (m_intersectStance)
    {
    
    case AgentIntersectStance::AGENT_STANCE_SWA_INTERSECT:
    {
        if (m_intersectA == other)
            return;
        m_intersectB = other;
        PushPair(m_intersectA, m_intersectB);
        m_intersectA = m_intersectB;
        
        //std::cout << "DDDdddDDDdDdD" << std::endl;
        break;
    }
    case AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT:
    {
        m_intersectA = other;
        m_intersectStance = AgentIntersectStance::AGENT_STANCE_SWA_INTERSECT;
        break;
    }
    }
}

const RenderLayerType Agent::GetLayerType() const modern_except_state
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void Agent::Remove()
{
    safe_remove();
}

void Agent::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 Agent::GetVector() modern_except_state
{
    return m_boundingSphere.Center;
}
