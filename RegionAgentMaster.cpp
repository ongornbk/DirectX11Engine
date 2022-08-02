#include "RegionAgentMaster.h"
#include "Global.h"
#include "EventManager.h"
#include "RendererManager.h"

RegionAgentMaster::RegionAgentMaster() : m_intersectStance(AgentIntersectStance::AGENT_STANCE_PRE_INTERSECT)
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_boundingSphere.Radius = 0.0f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = true;

    m_type = EObjectType::OBJECT_TYPE_REGION_AGENT;

    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DISABLED;
}

RegionAgentMaster::~RegionAgentMaster()
{
    if (m_text)
    {
        delete m_text;
        m_text = nullptr;
    }
}

void RegionAgentMaster::Initialize(const XMFLOAT2 position, Region* const parent)
{
    m_boundingSphere.Center.x = position.x;
    m_boundingSphere.Center.y = position.y;
    m_parent.make_handle(parent->GetHandle());
}

void _fastcall RegionAgentMaster::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
    if (m_flags.m_rendering)
    {
        shader.BeginInterface();
        //shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
        //shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
        //shader.SetShaderColorParameters(deviceContext, m_colorFilter);
       // m_vertexBuffer->Render(deviceContext);
        if (m_text)
        {
            m_text->Render(deviceContext, viewMatrix, projectionMatrix, shader.BeginInterface());
        }
    }
}

void _fastcall RegionAgentMaster::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
    if (m_flags.m_rendering)
    {
        shader.BeginShadow();
       //shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
       //shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
       //shader.SetShaderColorParameters(deviceContext, m_colorFilter);
       //m_vertexBuffer->Render(deviceContext);
        if (m_text)
        {
            m_text->PreRender(deviceContext, viewMatrix, projectionMatrix, shader.BeginShadow());
        }
    }
}

void RegionAgentMaster::Update(float dt)
{

    //m_flags.m_rendering = validateRendering(m_boundingSphere.Center);
    if (m_flags.m_rendering)
    {
        if (m_text)
        {
            m_text->Update();
        }
    }

}

void RegionAgentMaster::SetZ(float z)
{
}

void RegionAgentMaster::Release()
{
    m_flags.m_hide = true;
}

int32 RegionAgentMaster::isReleased() const modern_except_state
{
    return m_flags.m_hide;
}

void RegionAgentMaster::Intersect(EObject* const other)
{
    if (other == nullptr)
        return;
    if (other == this)
        return;
    if (other->m_boundingSphere.Radius == 0.f)
        return;

    class Region* const collline = (class Region* const)m_parent.get();
    //class Unit* const unit = (class Unit* const)(other);

    if (collline->m_rect.Intersects(other->m_boundingSphere))
    {

        if (collline->m_objects.insert(other->GetHandle()).second && collline->m_eventEntersBindStatus)
        {
            //std::cout << unit << " Enters: " << collline << std::endl;
            Global::GetInstance()->m_triggeringRegion.make_handle(collline->GetHandle());
            Global::GetInstance()->m_enteringObject.make_handle(other->GetHandle());
            EventManager::GetInstance()->EventRegionEntering();
        }
    }
    else
    {
        //unit->m_flags.m_pushable = true;
        if (collline->m_objects.erase(other->GetHandle()) && collline->m_eventLeavesBindStatus)
        {
            //std::cout << unit << " Leaves: " << collline << std::endl;
            Global::GetInstance()->m_triggeringRegion.make_handle(collline->GetHandle());
            Global::GetInstance()->m_leavingObject.make_handle(other->GetHandle());
            EventManager::GetInstance()->EventRegionLeaving();
        }
    }
}

const RenderLayerType RegionAgentMaster::GetLayerType() const modern_except_state
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void RegionAgentMaster::Remove()
{
    safe_remove();
}

void RegionAgentMaster::PostInitializeText()
{
    class Region* const collline = (class Region* const)m_parent.get();
    if(m_text)
            m_text->SetOffset({ collline->m_rect.Extents.x,0.f,0.f });
}

void RegionAgentMaster::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 RegionAgentMaster::GetVector() modern_except_state
{
    return m_boundingSphere.Center;
}

void RegionAgentMaster::SetText(std::string text)
{
    class TextFont* const font = RendererManager::GetInstance()->GetFont();
    if (font == nullptr)
        return;

    m_text = new Text;
    m_text->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), Engine::GetEngine()->GetGraphics()->GetDeviceContext(), font->GetShader(), font, 20.f);
    m_text->SetText(text);
    m_text->SetPosition(m_boundingSphere.Center);
}
