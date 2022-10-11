#include "Region.h"
#include "RendererManager.h"
#include "Timer.h"
#include "ActionRemoveObject.h"
#include "RegionAgent.h"
#include "IPP.h"

Region::Region(const DirectX::XMFLOAT2 pA, const DirectX::XMFLOAT2 pB) : ColorFilter(1.f, 1.f, 1.f, 1.f), m_scale(1.f, 1.f)
{

	pointA.make_handle((new RegionAgent())->GetHandle());
	pointB.make_handle((new RegionAgent())->GetHandle());

	class RegionAgent* const A = (class RegionAgent* const)pointA.get();
	class RegionAgent* const B = (class RegionAgent* const)pointB.get();

	A->Initialize(pA, this);
	B->Initialize(pB, this);

	XMVECTOR aV = { pA.x,pA.y,0.f,0.f };
	XMVECTOR bV = { pB.x,pB.y,0.f,0.f };

	BoundingBox::CreateFromPoints(m_rect, aV, bV);

	RendererManager::GetInstance()->PushRegionAgent(A);
	RendererManager::GetInstance()->PushRegionAgent(B);

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());


}

Region::Region(const float x1, const float y1, const float x2, const float y2) : ColorFilter(1.f, 1.f, 1.f, 1.f), m_scale(1.f, 1.f)
{
	pointA.make_handle((new RegionAgent())->GetHandle());
	pointB.make_handle((new RegionAgent())->GetHandle());

	class RegionAgent* const A = (class RegionAgent* const)pointA.get();
	class RegionAgent* const B = (class RegionAgent* const)pointB.get();

	A->Initialize(DirectX::XMFLOAT2(x1,y1), this);
	B->Initialize(DirectX::XMFLOAT2(x2, y2), this);

	XMVECTOR aV = { x1,y1,0.f,0.f };
	XMVECTOR bV = { x2,y2,0.f,0.f };

	BoundingBox::CreateFromPoints(m_rect, aV, bV);

	RendererManager::GetInstance()->PushRegionAgent(A);
	RendererManager::GetInstance()->PushRegionAgent(B);

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());

	//ipp::Console::Println(m_rect.Extents.y);
	//ipp::Console::Println(y2);
}

Region::~Region()
{
	m_objects.clear();
	((class RegionAgent* const)pointA.get())->Remove();
	((class RegionAgent* const)pointB.get())->Remove();

	class RenderAgent* const renderAgent = ((class RenderAgent* const)m_renderAgent.get());
	if (renderAgent)
	{
		renderAgent->Remove();
	}

	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}

	if (m_text)
	{
		delete m_text;
		m_text = nullptr;
	}
}

void _fastcall Region::Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader)
{
	if (m_text && m_texture)
	{
		shader.BeginInterface();
		shader.SetShaderParameters(deviceContext, m_texture->GetTexture());
		shader.SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		shader.SetShaderColorParameters(deviceContext, m_colorFilter);
		m_vertexBuffer->Render(deviceContext);
			m_text->Render(deviceContext, viewMatrix, projectionMatrix, shader.BeginInterface());
	}

}

void Region::Update(float dt)
{
	if (m_text && m_texture)
	{
		DirectX::XMStoreFloat4x4(&m_worldMatrix,
			DirectX::XMMatrixMultiply(
				DirectX::XMMatrixScaling(m_scale.x, m_scale.y, 1.f),
				DirectX::XMMatrixTranslation(
					m_rect.Center.x,
					m_rect.Center.y,
					m_rect.Center.z //- (m_size / 1.5f)
				)));

		if (m_text)
		{
			m_text->Update();
		}
	}
}

RegionAgent* const Region::GetSecond(RegionAgent* const first)
{
	class RegionAgent* const A = (class RegionAgent* const)pointA.get();
	class RegionAgent* const B = (class RegionAgent* const)pointB.get();
	if (first == A)
		return B;
	return A;
}

const modern_handle& Region::GetHandle()
{
	return m_object;
}

volatile modern_handle& Region::GetHandle() volatile
{
	return m_object;
}

void Region::GiveName(std::string name)
{



	ID3D11Device* const device = Engine::GetEngine()->GetGraphics()->GetDevice();
	Shader* const shader = ResourceManager::GetInstance()->GetShaderByName("texture.fx");

	if(device&&shader)
	{

		class TextFont* const font = RendererManager::GetInstance()->GetFont();
		if (font == nullptr)
			return;

		m_text = new Text;
		m_text->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), Engine::GetEngine()->GetGraphics()->GetDeviceContext(), font->GetShader(), font, 20.f);
		m_text->SetText(name);
		m_text->SetPosition(m_rect.Center);

		class RegionAgent* const A = (class RegionAgent* const)pointA.get();
		A->m_flags.m_rendering = true;

		m_vertexBuffer = new VertexBuffer();
		float sizexy[2] = { m_rect.Extents.x * 2.f,m_rect.Extents.y * 2.f };

		(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);

		m_texture = ResourceManager::GetInstance()->GetTextureByName("region");
		//{
		//	class RenderAgent* renderAgent = new RenderAgent();
		//	m_renderAgent.make_handle(renderAgent->GetHandle());
		//	renderAgent->Initialize(this);
		//	RendererManager::GetInstance()->PushRenderAgent(renderAgent);
		//}
	}
}

const enum DirectX::ContainmentType Region::Contains(GameObject* const object) const
{
	return m_rect.Contains(object->m_boundingSphere);
}

const bool Region::Intersects(GameObject* const object) const
{
	return m_rect.Intersects(object->m_boundingSphere);
}

const DirectX::XMFLOAT3& Region::GetPosition() const modern_except_state
{
	return m_rect.Center;
}

const RenderLayerType Region::GetRenderLayer() const modern_except_state
{
	return RenderLayerType::ENUM_OBJECT_TYPE;
}