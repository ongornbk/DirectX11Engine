#pragma once
#include "Sprite.h"




class RenderModel
{
public:
	RenderModel();
	virtual ~RenderModel();

	virtual void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader,WCHAR* filename);
	virtual void Update(float dt = 0.0f);
	virtual void Render(XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);

protected:

	VertexBuffer *        m_vertexBuffer;
	ID3D11DeviceContext * m_deviceContext;
	Shader*               m_shader;

public:

	enum
	{
		SUPERMODEL
	} ModelType;
};

