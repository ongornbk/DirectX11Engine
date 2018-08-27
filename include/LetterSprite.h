#pragma once
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Font.h"

class LetterSprite
{
public:

	LetterSprite(Font* font, char letter, float size,Shader* shader);

	virtual ~LetterSprite(void);

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader,Font* font);

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);

	void Update();

private:
	ID3D11DeviceContext * m_deviceContext;

	VertexBuffer* m_vertexBuffer;
	Texture*      m_texture;
	Shader*       m_shader;
	float         m_size;
	char          m_char;
};

