#include "Tree.h"
#include "ResourceManager.h"
#include "RendererManager.h"
#include "IPP.h"

namespace
{
	static Global* m_global = nullptr;
}

Tree::Tree()
{
	m_vertexBuffer = nullptr;
	m_texture = nullptr;
	m_deviceContext = nullptr;

	Center = XMFLOAT3(POSITION_ZERO_POINT_X, POSITION_ZERO_POINT_Y, POSITION_ZERO_POINT_Z);
	Radius = COLLISION_DISABLED_OR_NULL;
	m_flags[0] = TRUE;//rendering
	m_flags[1] = FALSE;//selected
	m_flags[2] = TRUE;//pushable
	m_flags[3] = FALSE;//blocked
	m_flags[4] = FALSE;//collision with tilemap
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
}


Tree::~Tree()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void Tree::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR * paths, float size, float collision, XMFLOAT3 position, bool pushable)
{
	m_size = size;


	m_vertexBuffer = new VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->InitializeAnchorBottom(device, shader, sizexy, true);

	if (paths != NULL)
	{
		wstring tmp0 = wstring(paths);
		string tmp1 = string(tmp0.begin(), tmp0.end());
		m_texture = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	m_deviceContext = deviceContext;


	m_flags[2] = pushable;

	Radius = collision;
	Center = position;
	Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix
	Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;//Collision fix

	//Center.y -= ((float)(m_size) / 2.0f);
	//Center.y += Radius;
	m_type = RenderContainer::RenderContainerType::TREE;
}

void Tree::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader)
{
	if (m_flags[0])
	{
		//shader.standard->End(deviceContext);
		//shader.shadow->Begin(deviceContext);
		//
		//auto cmm = Camera::GetCurrentCamera();
		//auto cpp = cmm->GetPosition();
		//
		////auto cxvm = XMLoadFloat3(&Center);
		//
		////auto cxm = XMVector2AngleBetweenVectors(cpp, cxvm);
		//
		//__m128 dist{};
		//dist.m128_f32[0] = cpp.m128_f32[1] - Center.y;
		//dist.m128_f32[1] = cpp.m128_f32[0] - Center.x;
		//
		//auto rot = atan2(dist.m128_f32[0], dist.m128_f32[1]);
		//
		//auto wms = XMMatrixRotationZ(rot+XM_PIDIV2);
		//
	//	//auto distL = XMVector2Length(dist).m128_f32[0];
		//
		////auto txscl = distL / 1000.0f;
		//
		////ipp::math::clamp(txscl, 0.0f, 3.0f);
		//
	//	//auto scl = XMMatrixScaling(distL / 1000.0f, distL / 1000.0f, distL / 1000.0f);
		//
		//
		//
		//wms = wms * XMLoadFloat4x4(&m_worldMatrix);// * scl;
		//XMFLOAT4X4 shadowMatrix;
		//XMStoreFloat4x4(&shadowMatrix, wms);
		//shader.shadow->SetShaderParameters(deviceContext, m_texture->GetTexture());
		//shader.shadow->SetShaderParameters(deviceContext,shadowMatrix , viewMatrix, projectionMatrix);
		//m_vertexBuffer->Render(deviceContext);
		//
		//shader.shadow->End(deviceContext);
		//shader.standard->Begin(deviceContext);

		shader.standard->SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.standard->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);

	}
}

void Tree::Update(float dt)
{
	m_flags[0] = validateRendering(Center);
	if (m_flags[0])
	{
		XMStoreFloat4x4(&m_worldMatrix, XMMatrixTranslation(Center.x, Center.y, Center.z));
	}
}

void Tree::SetZ(float z)
{
	Center.z = z;
}

BoundingSphere * Tree::GetBoundingSphere()
{
	return (BoundingSphere*)(this);
}

void Tree::Release()
{
	delete this;
}

bool Tree::Flag(uint8_t index)
{
	return m_flags[index];
}

void Tree::Flag(uint8_t index, bool boolean)
{
	m_flags[index] = boolean;
}

void Tree::SetGlobal(Global * global) noexcept
{
	m_global = global;
}
