#pragma once
#include "HandleIntersetionInfo.h"
#include "HandleType.h"
#include "gdef.h"
#include <DirectXCollision.h>


class Handle
{
	uint32           m_index;
	uint32           m_vector;
	int32            m_collisionPriority = 0;

	struct DirectX::BoundingSphere m_boundingSphere;

	enum class HandleType m_type;

public:

	virtual void            Update(const float dt = 0.f) = 0;
	virtual void            Release() = 0;
	virtual bool           isReleased() const noexcept = 0;

	virtual void _cdecl Intersect(class Handle* const other) = 0;

	
};

