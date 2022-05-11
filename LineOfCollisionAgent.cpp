#include "LineOfCollisionAgent.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "ActionGoBack.h"
#include "ActionNotifyBlock.h"
#include "Timer.h"
#include "LineOfCollision.h"

LineOfCollisionAgent::LineOfCollisionAgent() : m_intersectStance(AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT)
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_boundingSphere.Radius = 0.0f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = false;

    m_type = EObjectType::OBJECT_TYPE_LINE_COLLISION_AGENT;

    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DISABLED;
}

LineOfCollisionAgent::~LineOfCollisionAgent()
{
    
}

void LineOfCollisionAgent::Initialize(const XMFLOAT2 position, class LineOfCollision* const parent)
{
    m_boundingSphere.Center.x = position.x;
    m_boundingSphere.Center.y = position.y;
    m_parent.make_handle(parent->GetHandle());
}


void _fastcall LineOfCollisionAgent::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{

}

void _fastcall LineOfCollisionAgent::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void LineOfCollisionAgent::Update(float dt)
{
    class LineOfCollision* const collline = (class LineOfCollision* const)m_parent.get();
    class LineOfCollisionAgent* const second = collline->GetSecond(this);

    for (auto obj : collline->m_objects)
    {
        class Unit* const unit = (class Unit* const)(obj.get());
        if (unit == nullptr)
        {
            continue;
        }

        if (modern_xfloat3_distance2(unit->m_boundingSphere.Center,m_boundingSphere.Center,second->m_boundingSphere.Center) * 20.f< (unit->m_boundingSphere.Radius))
        {
            switch (unit->m_type)
            {
            case EObjectType::OBJECT_TYPE_UNIT:
            {
                //unit->m_flags.m_pushable = false;
                //unit->m_flags.m_collided = true;
                //unit->m_flags.m_collided = true;
                class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
                //action->push(new ActionGoBack(unit));
                action->push(new ActionNotifyBlock(unit, this));
                Timer::CreateInstantTimer(action);
                break;
            }
            }
        }
    }
    m_intersectStance = AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT;
}

void LineOfCollisionAgent::SetZ(float z)
{
}

void LineOfCollisionAgent::Release()
{
    m_flags.m_hide = true;
}

int32 LineOfCollisionAgent::isReleased() const noexcept
{
    return m_flags.m_hide;
}

void LineOfCollisionAgent::Intersect(EObject* const other)
{
    if (other == nullptr)
        return;
    if (other == this)
        return;
    if (other->m_boundingSphere.Radius == 0.f)
        return;

    class LineOfCollision* const collline = (class LineOfCollision* const)m_parent.get();
    class Unit* const unit = (class Unit* const)(other);

        if (collline->m_rect.Intersects(unit->m_boundingSphere))
        {

            if (collline->m_objects.insert(unit->GetHandle()).second)
            {

            }
        }
        else
        {
            //unit->m_flags.m_pushable = true;
            collline->m_objects.erase(unit->GetHandle());
        }
    
}

const RenderLayerType LineOfCollisionAgent::GetLayerType() const noexcept
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void LineOfCollisionAgent::Remove()
{
    class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
    action->push(new ActionRemoveObject(this));
    Timer::CreateInstantTimer(action);
}

void LineOfCollisionAgent::SetVector(const DirectX::XMFLOAT3& vec) noexcept
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 LineOfCollisionAgent::GetVector() noexcept
{
    return m_boundingSphere.Center;
}
