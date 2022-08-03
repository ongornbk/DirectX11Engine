#include "RectOfCollisionAgentSecond.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "ActionGoBack.h"
#include "Timer.h"
#include "RectOfCollision.h"

RectOfCollisionAgentSecond::RectOfCollisionAgentSecond() : m_intersectStance(AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT)
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_boundingSphere.Radius = 0.0f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = false;

    m_type = EObjectType::OBJECT_TYPE_RECT_COLLISION_AGENT;

    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DISABLED;
}

RectOfCollisionAgentSecond::~RectOfCollisionAgentSecond()
{
}

void RectOfCollisionAgentSecond::Initialize(const XMFLOAT2 position, class LineOfCollision* const parent)
{
    m_boundingSphere.Center.x = position.x;
    m_boundingSphere.Center.y = position.y;
    m_parent.make_handle(parent->GetHandle());
}

void _fastcall RectOfCollisionAgentSecond::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void _fastcall RectOfCollisionAgentSecond::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void RectOfCollisionAgentSecond::Update(float dt)
{
    class RectOfCollision* const collline = (class RectOfCollision* const)m_parent.get();
   // class RectOfCollisionAgentThird* const second = (class RectOfCollisionAgentThird* const)collline->pointB;
   //
   // for (auto obj : collline->m_objects)
   // {
   //     class Unit* const unit = (class Unit* const)(obj.get());
   //     if (unit == nullptr)
   //     {
   //         continue;
   //     }
   //
   //     if (modern_xfloat3_distance2(unit->m_boundingSphere.Center, m_boundingSphere.Center, second->m_boundingSphere.Center) * 20.f < (unit->m_boundingSphere.Radius))
   //     {
   //         switch (unit->m_type)
   //         {
   //         case EObjectType::OBJECT_TYPE_UNIT:
   //         {
   //
   //             unit->GoBack();
   //             Timer::CreateInstantTimer(new ActionGoBack(unit));
   //             if (unit->IsWandering())
   //             {
   //                 unit->DiscardTasks();
   //             }
   //             break;
   //         }
   //         }
   //     }
   // }
   // m_intersectStance = AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT;
}

void RectOfCollisionAgentSecond::SetZ(float z)
{
}

void RectOfCollisionAgentSecond::Release()
{
    m_flags.m_hide = true;
}

int32 RectOfCollisionAgentSecond::isReleased() const modern_except_state
{
    return m_flags.m_hide;
}

void RectOfCollisionAgentSecond::Intersect(EObject* const other)
{
    if (other == nullptr)
        return;
    if (other == this)
        return;
    if (other->m_boundingSphere.Radius == 0.f)
        return;

    class RectOfCollision* const collline = (class RectOfCollision* const)m_parent.get();
    class Unit* const unit = (class Unit* const)(other);

    if (collline->m_rect.Intersects(unit->m_boundingSphere))
    {

        if (collline->m_objects.insert(unit->GetHandle()).second)
        {

        }
    }
    else
    {
        collline->m_objects.erase(unit->GetHandle());
    }

}

const RenderLayerType RectOfCollisionAgentSecond::GetLayerType() const modern_except_state
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void RectOfCollisionAgentSecond::Remove()
{
    class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
    action->push(new ActionRemoveObject(this));
    Timer::CreateInstantTimer(action);
}

void RectOfCollisionAgentSecond::RemoveNow()
{
    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DELETE;
}

void RectOfCollisionAgentSecond::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 RectOfCollisionAgentSecond::GetVector() modern_except_state
{
    return m_boundingSphere.Center;
}
