#pragma once
#include "gdef.h"
#include "RenderContainer.h"
#include "ColorFilter.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Text.h"
#include "RenderAgent.h"
#include "RenderAgentParent.h"
#include <set>

class IRegionAgent;

class Region : public modern_class, public ColorFilter, public RenderAgentParent
{
	modern_handle pointA;
	modern_handle pointB;
	modern_handle m_renderAgent;
protected:
	friend class RegionAgent;
	std::set<modern_handle> m_objects;
	BoundingBox              m_rect;

	Text* m_text = nullptr;

	Texture* m_texture = nullptr;
	VertexBuffer* m_vertexBuffer = nullptr;
	XMFLOAT4X4    m_worldMatrix;
	XMFLOAT2      m_scale;
public:

	Region(const struct DirectX::XMFLOAT2 pA, const struct DirectX::XMFLOAT2 pB);
	Region(const float x1,const float y1,const float x2,const float y2);
	~Region();

	void _fastcall Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader);
	void Update(float dt);

	RegionAgent* const GetSecond(RegionAgent* const first);

	const modern_handle& GetHandle();
	volatile modern_handle& GetHandle() volatile;

	void Bind(std::string enters, std::string leaves);
	void BindEnters(std::string enters);
	void BindLeaves(std::string leaves);
	void Unbind();
	void GiveName(std::string name);

	const DirectX::XMFLOAT3& GetPosition()const noexcept;
	const enum class RenderLayerType GetRenderLayer() const noexcept override;
private:
	void Enters(const modern_handle& object);
	void Leaves(const modern_handle& object);

	friend class EventManager;
	friend class RegionAgent;
	friend class RegionAgentMaster;

	modern_Boolean m_eventEntersBindStatus = modern_false;
	modern_Boolean m_eventLeavesBindStatus = modern_false;

	std::string m_eventEnters;
	std::string m_eventLeaves;
};

