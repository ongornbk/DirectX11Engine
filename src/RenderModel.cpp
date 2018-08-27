#include "RenderModel.h"



RenderModel::RenderModel()
{
}


RenderModel::~RenderModel()
{
}

void RenderModel::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, WCHAR * filename)
{
	m_deviceContext = deviceContext;
	m_shader        = shader;
}

void RenderModel::Update(float dt)
{
}

void RenderModel::Render(XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_vertexBuffer->Render(m_deviceContext);
}

