#pragma once
#include "VertexBuffer.h"
#include "Texture.h"
#include "TextureShader.h"
#include "ColorFilter.h"
#include "modern/modern_def.h"

class Sprite : public ColorFilter
{
public:
	Sprite(float size);
	Sprite(float sizex, float sizey);
	virtual ~Sprite(void);

	virtual void Initialize(ID3D11Device* device, Shader* shader, WCHAR* textureFileName, bool isWriteable = false);
	virtual void InitializeRotated(ID3D11Device* device, Shader* shader, WCHAR* textureFileName, bool isWriteable = false);
	virtual void Update();
	virtual void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	virtual void Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader* shader);
	virtual bool ResizeTexture(ID3D11Device * device, float size, bool writeable = false);
	virtual void SetAnimationSpeed(float speed = 1.0f);
	virtual const struct DirectX::XMFLOAT2 GetSize() const modern_except_state;
protected:
	VertexBuffer* m_vertexBuffer;
	Texture* m_texture;
	Shader* m_shader;
	DirectX::XMFLOAT2 m_size;

};