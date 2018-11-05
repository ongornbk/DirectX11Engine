#pragma once
#include "Sprite.h"
#include "RenderContainer.h"

class Doodads : public RenderContainer, public BoundingSphere
{
public:
	Doodads();
	~Doodads();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* paths, float size, float collision, XMFLOAT3 position,bool pushable);

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	BoundingSphere* GetBoundingSphere() override;
	void Release() override;
	bool Flag(uint8_t index) override;
	void Flag(uint8_t index, bool boolean) override;

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3      m_lastPosition;
				  
	XMFLOAT4X4    m_worldMatrix;
	float         m_size;
	bool          m_flags[5];
				  
	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;
};

