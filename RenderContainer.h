#pragma once
#include "Model.h"
#include "SuperModel.h"
#include "TaskQueue.h"
#include "Types.h"

class RenderContainer
{
public:

	virtual void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader* shader) = 0;
	virtual void SetZ(float z = 0.0f) = 0;
	virtual void Update(float dt) = 0;
	virtual void Release() = 0;
	virtual bool Flag(uint8_t) = 0;
	virtual void Flag(uint8_t, bool boolean) = 0;
	virtual BoundingSphere* GetBoundingSphere() = 0;

public:
	uint32_t      m_index;
	enum RenderContainerType
	{
		UNIT,
		DOODADS,
		ANIMATED_DOODADS,
		TREE
	} m_type;
};

