#include "Interface.h"
#include "ResourceManager.h"
#include "RendererManager.h"
#include "ActionExecuteActionArray.h"
#include "ActionRemoveObject.h"
#include "Timer.h"

Interface::Interface() : ColorFilter(1.f,1.f,1.f,1.f)
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;
	m_parent = nullptr;
	m_behavior = nullptr;

	m_boundingSphere.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_boundingSphere.Radius = 0.0f;
	m_box.Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_box.Extents = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
}

Interface::~Interface()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
	if (m_behavior)
	{
		delete m_behavior;
		m_behavior = nullptr;
	}
}

void Interface::Initialize(
	struct ID3D11Device* const device,
	struct ID3D11DeviceContext* const deviceContext,
	class Shader* const shader,
	WCHAR* paths,
	const struct DirectX::XMFLOAT3 position,
	const float xsize,
	const float ysize
)
{
	//m_size = size;
	//m_size = 100.f;

	m_box.Center = position;
	m_box.Extents = DirectX::XMFLOAT3(xsize/2.f, ysize/2.f, 0.0f);

	m_vertexBuffer = new VertexBuffer();
	float sizexy[2] = { xsize,ysize };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);

	if (paths != NULL)
	{
		wstring tmp0 = wstring(paths);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	m_deviceContext = deviceContext;

	//m_boundingSphere.Radius = collision;
	m_boundingSphere.Center = position;
	//m_boundingSphere.Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	//m_boundingSphere.Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;

	m_type = EObject::EObjectType::OBJECT_TYPE_INTERFACE;
}

void _fastcall Interface::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
	if (m_flags.m_rendering)
	{
		shader.BeginInterface();
		shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		shader.SetShaderColorParameters(deviceContext, m_colorFilter);
		m_vertexBuffer->Render(deviceContext);
	}
	for (auto obj : m_children)
	{
		if (obj)
			obj->Render(deviceContext, viewMatrix, projectionMatrix, shader);
	}
}

void _fastcall Interface::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
	if (m_flags.m_cast_shadow)
	{
		shader.BeginShadow();
	}
}

void Interface::Remove()
{
	class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
	action->push(new ActionRemoveObject(this));
	Timer::CreateInstantTimer(action);
}

void Interface::Update(float dt)
{
	

	m_flags.m_rendering = validateRendering(m_boundingSphere.Center);
	if (m_flags.m_rendering)
	{
		DirectX::XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(m_boundingSphere.Center.x, m_boundingSphere.Center.y, m_boundingSphere.Center.z));
	}

	if (m_behavior)
	{
		m_behavior->OnHover();
	}

	for (auto obj : m_children)
	{
		if (obj)
			obj->Update(dt);
	}
}

void Interface::SetZ(float z)
{
	m_boundingSphere.Center.z = z;
}

void Interface::Release()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
	for (auto obj : m_children)
	{
		if (obj)
			obj->Release();
		obj = nullptr;
	}
}

int32 Interface::isReleased() const noexcept
{
	if (m_vertexBuffer)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void _cdecl Interface::Intersect(EObject* const other)
{
}

const RenderLayerType Interface::GetLayerType() const noexcept
{
	return RenderLayerType::ENUM_INTERFACE_TYPE;
}

void Interface::SetParent(Interface* const parent)
{
	m_parent = parent;
}

void Interface::SetBehavior(IInterfaceBehavior* const behavior)
{
	if (m_behavior)
	{
		delete m_behavior;
	}
	m_behavior = behavior;
}

void Interface::PushChild(EObject* const child)
{
	m_children.push_back(child);
}

Interface* const Interface::GetParent() const noexcept
{
	return m_parent;
}
