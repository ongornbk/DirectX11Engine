#pragma once
#include "Sprite.h"
#include "RenderContainer.h"

class Doodads : public RenderContainer
{
public:
	Doodads();
	~Doodads();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* paths, float size, float collision, XMFLOAT3 position,RenderContainerFlags flags);

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	void Release() override;

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3      m_lastPosition;
				  
	XMFLOAT4X4    m_worldMatrix;
	float         m_size;
				  
	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;
};

