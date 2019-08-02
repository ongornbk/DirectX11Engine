#pragma once
#include "Sprite.h"
#include "RenderContainer.h"

class Doodads : public EObject
{
public:
	Doodads();
	~Doodads();

	void Initialize(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		class Shader* shader,
		WCHAR* paths,
		const float size,
		const float collision,
		const XMFLOAT3 position
	);

	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void Update(const float dt) override;
	void SetZ(const float z = 0.0f) override;
	void Release() override;
	int32 isReleased() const noexcept override;

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3      m_lastPosition;
				  
	XMFLOAT4X4    m_worldMatrix;
	float         m_size;
				  
	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;
};

