#pragma once
#include "TaskQueue.h"
#include "Types.h"
#include "ShaderPackage.h"
#include <DirectXCollision.h>

struct RenderContainerFlags
{



	union
	{

		struct
		{
			bool m_rendering;
			bool m_selected;
			bool m_pushable;
			bool m_blocked;
			bool m_collided;
			bool m_selectable;
			bool m_cast_shadow;
			bool m_UNDECLARED_YET;
		};

		uint64_t m_flags{};
		bool     m_flag[8];

	};
};

enum RenderContainerAnchor
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

class RenderContainer : public RenderContainerFlags
{
public:

	virtual void            Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) = 0;
	virtual void            SetZ(float z = 0.0f) = 0;
	virtual void            Update(float dt) = 0;
	virtual void            Release() = 0;
	virtual BoundingSphere* GetBoundingSphere() = 0;


public:
	uint32_t             m_index;
	

	enum RenderContainerType
	{
		UNIT,
		DOODADS,
		ANIMATED_DOODADS,
		TREE
	}m_type;
};

