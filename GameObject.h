#pragma once
#include "gdef.h"
#include "TaskQueue.h"
#include "ShaderPackage.h"
#include "RenderLayerType.h"
#include "ObjectManagementType.h"
#include "ObjectIntersectionInfo.h"
#include "ObjectAnchorType.h"
#include "ObjectFlags.h"
#include "CompileTimeEnumManager.h"
#include "GameObjectType.h"
#include <DirectXCollision.h>

class GameObject : public modern_class
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
	virtual void RemoveNow() = 0;

	virtual void               SetZ(const float z = 0.f)                              = 0;
	virtual void               Update(const float dt = 0.f)                           = 0;
	virtual void               Release()                                              = 0;
	virtual int32              isReleased()                            const modern_except_state = 0;
	virtual DirectX::XMFLOAT3  GetVector()                             modern_except_state = 0;
	virtual void               SetVector(const DirectX::XMFLOAT3& vec) modern_except_state = 0;

	virtual void Intersect(class GameObject* const other) = 0;
	virtual const enum class RenderLayerType GetLayerType() const modern_except_state = 0;

public:
	uint32           m_index;
	uint32           m_vector;

	virtual ~GameObject();

	int32 collisionPriority = 0;

	DirectX::BoundingSphere m_boundingSphere;

	struct ObjectFlags m_flags;

	volatile enum class ObjectManagementType m_managementType;
	
	struct GameObjectTypeInterface* m_type_v2;

	enum class GameObjectType m_type;

	class GameObject* const GetClosestObject() const modern_except_state;

	const modern_handle& GetHandle();
	modern_handle* const GetHandlePtr();
	modern_handle* const GetNewHandlePtr();
	volatile modern_handle& GetHandle() volatile;

	const virtual struct DirectX::XMFLOAT3& __vectorcall GetPosition() modern_except_state;
	const virtual float GetCollisionRadius() const modern_except_state;

protected:
	void safe_remove() modern_except_state;
};

