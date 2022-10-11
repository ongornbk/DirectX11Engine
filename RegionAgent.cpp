#include "RegionAgent.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"
#include "EventManager.h"
#include "Global.h"
#include "IPP.h"

RegionAgent::RegionAgent()
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_boundingSphere.Radius = 0.0f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = false;

    m_type = EObjectType::OBJECT_TYPE_REGION_AGENT;

    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DISABLED;
}

RegionAgent::~RegionAgent()
{

}

void RegionAgent::Initialize(const XMFLOAT2 position, class Region* const parent)
{
    m_boundingSphere.Center.x = position.x;
    m_boundingSphere.Center.y = position.y;
    m_parent.make_handle(parent->GetHandle());
}


void _fastcall RegionAgent::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{

}

void _fastcall RegionAgent::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void RegionAgent::Update(float dt)
{
}

void RegionAgent::SetZ(float z)
{
}

void RegionAgent::Release()
{
    m_flags.m_hide = true;
}

int32 RegionAgent::isReleased() const modern_except_state
{
    return m_flags.m_hide;
}

void RegionAgent::Intersect(GameObject* const other)
{
    if (other == nullptr)
        return;
    if (other == this)
        return;
    if (other->m_boundingSphere.Radius == 0.f)
        return;

    class Region* const region = (class Region* const)m_parent.get();
   
    if (region->m_rect.Contains(other->m_boundingSphere)==DirectX::ContainmentType::DISJOINT)
    {
        if (region->m_objects.erase(other->GetHandlePtr()))
        {
            region->OnLeave(other->GetHandle());
        }
        else
        {
           // ipp::Console::Println(other);
        }
    }
    else
    {
        if (region->m_objects.insert(other->GetNewHandlePtr()).second)
        {
            region->OnEnter(other->GetHandle());
        }
    }

}

const RenderLayerType RegionAgent::GetLayerType() const modern_except_state
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void RegionAgent::Remove()
{
    safe_remove();
}

void RegionAgent::RemoveNow()
{
    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DELETE;
}

void RegionAgent::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 RegionAgent::GetVector() modern_except_state
{
    return m_boundingSphere.Center;
}