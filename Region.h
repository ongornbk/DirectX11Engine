#pragma once
#include "gdef.h"
#include "RenderContainer.h"
#include "ColorFilter.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Text.h"
#include "RenderAgent.h"
#include "RenderAgentParent.h"
#include "Global.h"		  //To be removed
#include "EventManager.h" //To be removed
#include <set>

class IRegionAgent;

class Region : public modern_class, public ColorFilter, public RenderAgentParent
{
protected:
	friend class RegionAgent;

	modern_handle pointA;
	modern_handle pointB;
	modern_handle m_renderAgent;
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
	virtual ~Region();

	void _fastcall Render(ID3D11DeviceContext* const deviceContext, const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projectionMatrix, const ShaderPackage& shader);
	void Update(float dt);

	RegionAgent* const GetSecond(RegionAgent* const first);

	const modern_handle& GetHandle();
	volatile modern_handle& GetHandle() volatile;

	void GiveName(std::string name);

	const DirectX::XMFLOAT3& GetPosition()const modern_except_state;
	const enum class RenderLayerType GetRenderLayer() const modern_except_state override;

	const enum DirectX::ContainmentType Contains(class EObject* const object) const;
	const bool Intersects(class EObject* const object) const;
private:
	void Enters(const modern_handle& object);
	void Leaves(const modern_handle& object);

	virtual void OnEnter(const class modern_handle& enteringObject) = 0;		 
	virtual void OnLeave(const class modern_handle& leavingObject) = 0;			 

	friend class RegionAgent;
	friend class RegionAgentMaster;


};



