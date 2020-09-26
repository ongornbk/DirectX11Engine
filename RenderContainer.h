#pragma once
#include "gdef.h"
#include "TaskQueue.h"
#include "ShaderPackage.h"
#include "RenderLayerType.h"
#include <DirectXCollision.h>


enum class EObjectIntersectionInfo
{
	NONE,
	INTERSECT,
	STOP
};

enum EObjectAnchor
{
	BOTTOM_CENTRE,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	TOP_LEFT,
	TOP_CENTRE,
	TOP_RIGHT,
	RIGHT,
	LEFT,
	CENTRE
};

struct EObjectFlags
{
	bool m_rendering = false;
	bool m_selected = false;
	bool m_pushable = false;
	bool m_blocked = false;
	bool m_collided = false;
	bool m_selectable = false;
	bool m_cast_shadow = false;
	bool m_hide = false;
};

class EObject
{
public:

	_Use_decl_annotations_
	virtual void _fastcall            Render(
		struct _In_ ID3D11DeviceContext* const deviceContext,
		const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
		const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
		const struct _In_ ShaderPackage &shader
	) = 0;

	_Use_decl_annotations_
	virtual void _fastcall           PreRender(
		struct ID3D11DeviceContext* _In_ const deviceContext,
		const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
		const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
		const struct _In_ ShaderPackage &shader
	) = 0;
	virtual void            SetZ(const float z = 0.f) = 0;
	virtual void            Update(const float dt = 0.f) = 0;
	virtual void            Release() = 0;
	virtual int32           isReleased() const noexcept = 0;

	virtual void _cdecl Intersect(class EObject* const other) = 0;
	virtual const enum class RenderLayerType GetLayerType() const noexcept = 0;

public:
	uint32           m_index;
	uint32           m_vector;



	int32 collisionPriority = 0;

	DirectX::BoundingSphere m_boundingSphere;

	struct EObjectFlags m_flags;

	enum class EObjectType
	{
		UNIT,
		DOODADS,
		ANIMATED_DOODADS,
		TREE,
		COLLISION_BOX,
		SPECIAL_EFFECT,
		REGION_POINT
	}m_type;
};

