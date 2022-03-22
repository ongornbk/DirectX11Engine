#include "Projectile.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
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
        shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
        shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
        m_vertexBuffer->Render(deviceContext);
    }
}

void _fastcall Projectile::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
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

int32 Projectile::isReleased() const noexcept
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
            if (owner != target)
            {
                modern_shared_guard guard(owner);
                if (modern_xfloat3_distance2(m_boundingSphere.Center, target->GetPosition()) < (m_collision + target->GetCollisionRadius()))
                {
                    target->DoDamage(owner);
                    class IAction* const action = new ActionRemoveObject(this);
                    Timer::CreateInstantTimer(action);
                    m_flags.m_hide = true;
                }
            }

        }
    }
}

const RenderLayerType Projectile::GetLayerType() const noexcept
{
    return RenderLayerType::ENUM_OBJECT_TYPE;
}

void Projectile::Remove()
{
    class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
    action->push(new ActionRemoveObject(this));
    Timer::CreateInstantTimer(action);
}

void Projectile::SetVector(const DirectX::XMFLOAT3& vec) noexcept
{
    m_boundingSphere.Center = vec;
}

DirectX::XMFLOAT3 Projectile::GetVector() noexcept
{
    return m_boundingSphere.Center;
}
