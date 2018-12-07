#pragma once
#include "TaskQueue.h"
#include "Types.h"
#include "ShaderPackage.h"
#include <DirectXCollision.h>

struct RenderContainerFlags 
{

	RenderContainerFlags() : m_flags(0u) {}
	


	RenderContainerFlags(std::string str)
	{
		SetFlags(str);
	}

	void SetFlags(std::string str)
	{
		for (int32_t i = 0; i < 8; i++)
		{
			if (str[i] == '1')
				m_flag[i] = true;
			else m_flag[i] = false;
		}
	}

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
			bool m_hide;
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

class RenderContainer : public RenderContainerFlags, public BoundingSphere
{
public:

	virtual void            Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) = 0;
	virtual void            SetZ(float z = 0.0f) = 0;
	virtual void            Update(float dt) = 0;
	virtual void            Release() = 0;


public:
	uint32_t             m_index;
	uint32_t             m_vector;

	enum RenderContainerType
	{
		UNIT,
		DOODADS,
		ANIMATED_DOODADS,
		TREE
	}m_type;
};

