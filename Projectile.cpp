#include "Projectile.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "ActionErasePack4.h"
#include "ActionErasePack2.h"
#include "Timer.h"

Projectile::Projectile()
{
    m_boundingSphere.Center = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
    m_boundingSphere.Radius = 0.f;
    m_flags.m_hide = false;//Release
    m_flags.m_pushable = false;
    m_flags.m_selectable = false;
    m_flags.m_rendering = true;

    m_vertexBuffer = nullptr;
    m_texture = nullptr;

    XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

    m_type = EObjectType::OBJECT_TYPE_PROJECTILE;
}

Projectile::~Projectile()
{
    if (m_vertexBuffer)
    {
        delete m_vertexBuffer;
        m_vertexBuffer = nullptr;
    }

    auto ite = GLOBAL m_mp2.find(&m_object);
    if (ite != GLOBAL m_mp2.end())
    {
        auto& ss = (*ite).second;
        for (auto ele = ss->begin();ele != ss->end();ele++)
        {
            delete* ele;
       }
        ss->clear();
        delete ss;
        GLOBAL m_mp2.erase(ite);
    }
    
}

void Projectile::Initialize(
	struct ID3D11Device* const device,
	struct ID3D11DeviceContext* const deviceContext,
	class Shader* const shader,
	WCHAR* path,
    const float size,
	const float collision,
	const struct DirectX::XMFLOAT3& position,
	const struct DirectX::XMFLOAT3& velocity,
    class Unit* const owner)
{
	//m_boundingSphere.Radius = collision;
	m_boundingSphere.Center = position;

    m_owner.make_handle(owner->GetHandle());

    m_size = size;
    m_velocity = velocity;
    m_collision = collision;

    m_vertexBuffer = new class VertexBuffer();
    float sizexy[2] = { m_size,m_size };
    (void)m_vertexBuffer->Initialize(device, shader, sizexy, true);

    if (path != NULL)
    {
        wstring tmp0 = wstring(path);
        string tmp1 = string(tmp0.begin(), tmp0.end());
        m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
    }

    //m_deviceContext = deviceContext;
}

void _fastcall Projectile::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
    if (m_flags.m_rendering)
    {
        DirectX::XMMATRIX rotationMatrix = XMMatrixRotationZ(atan2f(m_velocity.y,m_velocity.x)) * XMLoadFloat4x4(&m_worldMatrix);
        DirectX::XMStoreFloat4x4(&m_worldMatrix, rotationMatrix);
        shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
        shader.SetShaderParameters(deviceContext,m_worldMatrix, viewMatrix, projectionMatrix);
        m_vertexBuffer->Render(deviceContext);
    }
}

void _fastcall Projectile::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
    //if (m_flags.m_rendering)
    //{
    //    DirectX::XMMATRIX shadowrotationMatrix = XMMatrixRotationZ(atan2f(m_velocity.y, m_velocity.x)) * XMLoadFloat4x4(&m_worldMatrix) * XMMatrixTranslation(16.f, 16.f, 0.f);
    //    DirectX::XMStoreFloat4x4(&m_worldMatrix, shadowrotationMatrix);
    //    shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
    //    shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
    //    m_vertexBuffer->Render(deviceContext);
    //}
}

void Projectile::Update(float dt)
{
   m_boundingSphere.Center = modern_xfloat3_sum(m_boundingSphere.Center, modern_xfloat3_multiply(m_velocity, dt));
   if (m_flags.m_rendering)
   {
       DirectX::XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(m_boundingSphere.Center.x, m_boundingSphere.Center.y, m_boundingSphere.Center.z));
   }
}

void Projectile::SetZ(float z)
{
}

void Projectile::Release()
{
    m_flags.m_hide = true;
}

int32 Projectile::isReleased() const modern_except_state
{
    return m_flags.m_hide;
}

void Projectile::Intersect(EObject* const other)
{
    if (m_flags.m_hide == false)
    {
        //other already guarded
        if (other->m_type == EObjectType::OBJECT_TYPE_UNIT)
        {
            //owner not guarded
            class Unit* const owner = (class Unit* const)m_owner.get();
            class Unit* const target = (class Unit* const)other;
            if (owner && owner != target&& owner->GetOwner().get() != target->GetOwner().get())
            {
                modern_shared_guard guard(owner);
                
                const float distance = modern_xfloat3_distance2(m_boundingSphere.Center, target->GetPosition());
                const float soundDistance = modern_xfloat3_distance2(Camera::GetCurrentCamera()->GetPosition(), target->GetPosition());
                if (distance < (m_collision + target->GetCollisionRadius()))
                {
                   // struct modern_pack2* const pck2 = new struct modern_pack2(this, target);

                    auto ite = GLOBAL m_mp2.find(&m_object);
                    if (ite == GLOBAL m_mp2.end())
                    {
                        std::set<class modern_handle*, modern_handle_less>* mss = (new std::set<class modern_handle*, modern_handle_less>);
                        mss->insert(target->GetNewHandlePtr());
                        GLOBAL m_mp2[&m_object] = mss;
                    }
                    else
                    {
                        auto ddddd = (*ite).second->insert(target->GetNewHandlePtr());
                        if (ddddd.second)
                        {
                           // class IAction* const action = new ActionErasePack2(pck2);
                           // Timer::CreateExpiringTimer(action, 1.0f);
                           // target->GetHit(owner);
                           // target->DoDamage(owner);
                           // Engine* const engine = Engine::GetEngine();
                           // engine->PlaySound(L"impact_arrow", modern_clamp_reverse_div(soundDistance, 0.f, 1000.f) * 100.f);
                        }
                        else
                        {
                            return;
                        }
                    }

                    {
                        target->GetHit(owner);
                        target->DoDamage(owner);
                        Engine* const engine = Engine::GetEngine();
                        engine->PlaySound(L"impact_arrow", modern_clamp_reverse_div(soundDistance, 0.f, 1000.f) * 100.f);
                    }

                }
            }

        }
    }
}

const RenderLayerType Projectile::GetLayerType() const modern_except_state
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void Projectile::Remove()
{
    class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
    action->push(new ActionRemoveObject(this));
    Timer::CreateInstantTimer(action);
}

void Projectile::RemoveNow()
{
    m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DELETE;
}

void Projectile::SetVector(const DirectX::XMFLOAT3& vec) modern_except_state
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 Projectile::GetVector() modern_except_state
{
    return m_boundingSphere.Center;
}
