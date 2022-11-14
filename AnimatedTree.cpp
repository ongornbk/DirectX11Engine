#include "AnimatedTree.h"
#include "ResourceManager.h"
#include "CScripts.h"

AnimatedTree::AnimatedTree() :
    ColorFilter(1.f, 1.f, 1.f, 1.f)
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_boundingSphere.Radius = 0.0f;

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

	m_stance = 0;

	m_currentFrame = 0.f;
	m_stopped = false;
	m_isLooping = true;
	m_animationSpeed = 0.20f;
	m_framesPerSecond = 1.0f;
	m_currentSpeed = 0.0f;
	m_previousSpeed = 0.f;
	m_stop = false;
	m_rotations = 1.0f;
	m_size = 0.f;

	enable();
}

AnimatedTree::~AnimatedTree()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void AnimatedTree::Initialize(
	ID3D11Device* device,
	ID3D11DeviceContext* deviceContext,
	Shader* shader,
	WCHAR* paths,
	const float size,
	const float collision,
	const XMFLOAT3 position
)
{
	m_size = size;

	m_vertexBuffer = new class VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->InitializeAnchorBottom(device, shader, sizexy, true);

	if (paths != NULL)
	{
		wstring tmp0 = wstring(paths);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	m_deviceContext = deviceContext;

	m_boundingSphere.Radius = collision;
	m_boundingSphere.Center = position;
	m_boundingSphere.Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	m_boundingSphere.Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;

	m_fadeRegion.make_handle((new class RegionC(
		m_boundingSphere.Center.x - (m_size / 2.f),
		m_boundingSphere.Center.y + m_size,
		m_boundingSphere.Center.x + (m_size / 2.f),
		m_boundingSphere.Center.y,
		c_script_tree_fade_enter,
		c_script_tree_fade_leave
	))->GetHandle());

	//ipp::Console::Println(m_size);

	{
		class RegionC* const loc_reg = (class RegionC* const)m_fadeRegion.get();
		loc_reg->SetParent(this_handle);
	}

	class Region* const mfr = (class Region* const)(m_fadeRegion.get());
	if (mfr)
	{
		modern_guard g(mfr);
		mfr->GiveName("animated_tree");
	}

	m_type = GameObjectType::OBJECT_TYPE_TREE;
}

void _fastcall AnimatedTree::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void _fastcall AnimatedTree::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
}

void AnimatedTree::Update(float dt)
{
}

void AnimatedTree::SetZ(float z)
{
}

void AnimatedTree::Release()
{
}

int32 AnimatedTree::isReleased() const
{
    return int32();
}

void AnimatedTree::Intersect(GameObject* const other)
{
}

const RenderLayerType AnimatedTree::GetLayerType() const
{
    return RenderLayerType();
}

void AnimatedTree::Remove()
{
}

void AnimatedTree::RemoveNow()
{
}

void AnimatedTree::CastShadow(const bool shadow)
{
}

void AnimatedTree::SetVector(const DirectX::XMFLOAT3& vec)
{
}

DirectX::XMFLOAT3 AnimatedTree::GetVector()
{
    return DirectX::XMFLOAT3();
}

void AnimatedTree::SetStance(const modern_Boolean stance)
{
}

const modern_Boolean AnimatedTree::GetStance() const
{
    return modern_Boolean();
}

void AnimatedTree::SetGlobal(Global* global)
{
}

RenderHandle AnimatedTree::GetRenderHandle()
{
    return RenderHandle(m_texture, m_vertexBuffer);
}

inline void AnimatedTree::enable()
{
}

inline void AnimatedTree::disable()
{
}
