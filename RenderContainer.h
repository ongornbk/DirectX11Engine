#pragma once
#include "gdef.h"
#include "TaskQueue.h"
#include "ShaderPackage.h"
#include "RenderLayerType.h"
#include "ObjectManagementType.h"
#include "ObjectIntersectionInfo.h"
#include "ObjectAnchorType.h"
#include "ObjectFlags.h"
#include "modern/modern_class.h"
#include <DirectXCollision.h>

class EObject : public modern_class
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

	virtual void Remove() = 0;

	virtual void               SetZ(const float z = 0.f)                              = 0;
	virtual void               Update(const float dt = 0.f)                           = 0;
	virtual void               Release()                                              = 0;
	virtual int32              isReleased()                            const noexcept = 0;
	virtual DirectX::XMFLOAT3  GetVector()                             noexcept       = 0;
	virtual void               SetVector(const DirectX::XMFLOAT3& vec) noexcept       = 0;

	virtual void Intersect(class EObject* const other) = 0;
	virtual const enum class RenderLayerType GetLayerType() const noexcept = 0;

public:
	uint32           m_index;
	uint32           m_vector;

	virtual ~EObject();

	int32 collisionPriority = 0;

	DirectX::BoundingSphere m_boundingSphere;

	struct ObjectFlags m_flags;

	volatile enum class ObjectManagementType m_managementType;

	enum class EObjectType
	{
		OBJECT_TYPE_UNIT,
		OBJECT_TYPE_DOODADS,
		OBJECT_TYPE_ANIMATED_DOODADS,
		OBJECT_TYPE_TREE,
		OBJECT_TYPE_COLLISION_BOX,
		OBJECT_TYPE_SPECIAL_EFFECT,
		OBJECT_TYPE_REGION_POINT,
		OBJECT_TYPE_SHADOW,
		OBJECT_TYPE_AGENT,
		OBJECT_TYPE_INTERFACE,
		OBJECT_TYPE_PROJECTILE,
		OBJECT_TYPE_LINE_COLLISION_AGENT,
		OBJECT_TYPE_RECT_COLLISION_AGENT,
		OBJECT_TYPE_NPC
	}m_type;

	const modern_handle& GetHandle();
	volatile modern_handle& GetHandle() volatile;
};

