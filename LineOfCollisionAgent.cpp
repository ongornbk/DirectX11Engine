#include "LineOfCollisionAgent.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "ActionGoBack.h"
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
    m_intersectStance = AgentIntersectStance::AGENT_STANCE_DIS_INTERSECT;
    for (auto obj : collline->m_objects)
    {
        class LineOfCollision* const collline = (class LineOfCollision* const)m_parent.get();
        class LineOfCollisionAgent* const second = collline->GetSecond(this);
        class Unit* const unit = (class Unit* const)(obj.get());
        if (unit == nullptr)
        {
            continue;
        }
        //
        float ao = modern_xfloat3_distance2(m_boundingSphere.Center, unit->m_boundingSphere.Center);
        float bo = modern_xfloat3_distance2(second->m_boundingSphere.Center, unit->m_boundingSphere.Center);
        float ab = modern_xfloat3_distance2(m_boundingSphere.Center, second->m_boundingSphere.Center);
        
        float pl = (ao + bo + ab) / 2.f;
        
        float Ppl = sqrtf((pl - ao) * (pl - bo) * (pl - ab));
        
        float he = 40.f * Ppl / ab;
        //std::cout << "::  :: " << he << " :: " << unit->m_boundingSphere.Radius << std::endl;
        if (he < unit->m_boundingSphere.Radius)
        {
            switch (unit->m_type)
            {
            case EObjectType::OBJECT_TYPE_UNIT:
            {
                
               // unit->GoBack();
                Timer::CreateInstantTimer(new ActionGoBack(unit));
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


   //switch (m_intersectStance)
   //{
   //
   //case AgentIntersectStance::AGENT_STANCE_SWA_INTERSECT:
   //{
   //    if (m_intersectA == other)
   //        return;
   //    m_intersectB = other;
   //    PushPair(m_intersectA, m_intersectB);
   //    m_intersectA = m_intersectB;
   //
   //    //std::cout << "DDDdddDDDdDdD" << std::endl;
   //    break;
   //}
   //case AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT:
   //{
   //    m_intersectA = other;
   //    m_intersectStance = AgentIntersectStance::AGENT_STANCE_SWA_INTERSECT;
   //    break;
   //}
   //}

    class LineOfCollision* const collline = (class LineOfCollision* const)m_parent.get();
    //class LineOfCollisionAgent* const second = collline->GetSecond(this);
    class Unit* const unit = (class Unit* const)(other);
    //
    //float ao = modern_xfloat3_distance2(m_boundingSphere.Center, other->m_boundingSphere.Center);
    //float bo = modern_xfloat3_distance2(second->m_boundingSphere.Center, other->m_boundingSphere.Center);
    //float ab = modern_xfloat3_distance2(m_boundingSphere.Center, second->m_boundingSphere.Center);
    //
    //float pl = (ao + bo + ab) / 2.f;
    //
    //float Ppl = sqrtf((pl - ao) * (pl - bo) * (pl - ab));
    //
    //float he = 2.f * Ppl / ab;
    //
    //if (he < unit->m_boundingSphere.Radius)
    //{
    //    switch (other->m_type)
    //    {
    //    case EObjectType::OBJECT_TYPE_UNIT:
    //    {
    //        
    //       // unit->GoBack();
    //        Timer::CreateInstantTimer(new ActionGoBack(unit));
    //        break;
    //    }
    //    }
    //}
    //else
    //{
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
