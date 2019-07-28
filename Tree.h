#pragma once
#include "Sprite.h"
#include "RenderContainer.h"
#include "Global.h"

class Tree : public EObject
{
public:
	Tree();
	~Tree();

	void Initialize(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		class Shader* shader,
		WCHAR* paths,
		const float size,
		const float collision,
		const XMFLOAT3 position
	);

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	void Release() override;

	static void SetGlobal(Global* global) noexcept;

private:

	ID3D11DeviceContext* m_deviceContext;

	XMFLOAT3      m_lastPosition;

	XMFLOAT4X4    m_worldMatrix;
	float         m_size;

	Texture*      m_texture;
	VertexBuffer* m_vertexBuffer;
};

