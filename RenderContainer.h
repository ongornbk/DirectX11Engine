#pragma once
#include "gdef.h"
#include "TaskQueue.h"
#include "ShaderPackage.h"
#include "RenderLayerType.h"
#include "ObjectManagementType.h"
#include "ObjectIntersectionInfo.h"
#include "ObjectAnchorType.h"
#include "ObjectFlags.h"
#include <DirectXCollision.h>

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

	struct ObjectFlags m_flags;

	enum class ObjectManagementType m_managementType;

	enum class EObjectType
	{
		UNIT,
		DOODADS,
		ANIMATED_DOODADS,
		TREE,
		COLLISION_BOX,
		SPECIAL_EFFECT,
		REGION_POINT,
		SHADOW
	}m_type;
};

