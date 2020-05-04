#include "LetterSprite.h"
#include "ResourceManager.h"
#include "IPP.h"


LetterSprite::LetterSprite(
	class Font * const font,
	const char letter,
	const float size,
	class Shader* const shader
)
{

#pragma warning(disable : 4996)

	this->m_shader = shader;
	this->m_vertexBuffer = nullptr;
	this->m_size = size;
	this->m_char = letter;

	string fontname = font->GetName();

	char *buffer = new char[fontname.size() + 1];
	strcpy(buffer, fontname.c_str());
	this->m_texture = ResourceManager::GetInstance()->GetTextureByName(buffer);
	delete[] buffer;

}

LetterSprite::~LetterSprite(void)
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = NULL;
	}
}

void LetterSprite::Initialize(
	struct ID3D11Device * const device,
	struct ID3D11DeviceContext * const deviceContext,
	class Shader * const shader,
	class Font* const font
)
{
	m_vertexBuffer = new class VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	struct FLOATX6 coords = font->GetCoordsOfLetter(m_char);
	(void)m_vertexBuffer->InitializePart(device, shader, sizexy,coords.__f32, true);
}

void LetterSprite::Render(
	struct ID3D11DeviceContext * const deviceContext,
	DirectX::XMFLOAT4X4& worldMatrix,
	DirectX::XMFLOAT4X4& viewMatrix,
	DirectX::XMFLOAT4X4& projectionMatrix
)
{
	m_shader->SetShaderParameters(deviceContext,m_texture->GetTexture());
	m_shader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(deviceContext);
}

void LetterSprite::Update()
{


}
