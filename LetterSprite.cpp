#include "LetterSprite.h"
#include "ResourceManager.h"
#include "IPP.h"

namespace
{
	static struct DirectX::XMFLOAT4X4 s_world;
}

LetterSprite::LetterSprite(
	class TextFont* const font,
	const char letter,
	const float size)
{
#pragma warning(disable : 4996)

	this->m_vertexBuffer = nullptr;
	this->m_size = size;
	this->m_char = letter;

	string fontname = font->GetName();

	if (m_char != ' ')
	{
		char* buffer = new char[fontname.size() + 1];
		strcpy(buffer, fontname.c_str());
		this->m_texture = ResourceManager::GetInstance()->GetTextureByName(buffer);
		delete[] buffer;
	}
	
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
	class TextFont* const font
)
{
	if (m_char == ' ')
	{
		float sizexy[2] = { m_size,m_size };
		struct FLOATX6 coords = font->GetCoordsOfLetter('W');
	}
	else
	{
		m_vertexBuffer = new class VertexBuffer();
		float sizexy[2] = { m_size,m_size };
		struct FLOATX6 coords = font->GetCoordsOfLetter(m_char);
		(void)m_vertexBuffer->InitializePart(device, shader, sizexy, coords.__f32, true);
	}
}

void LetterSprite::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct DirectX::XMFLOAT4X4& world,
	const struct DirectX::XMFLOAT4X4& viewMatrix,
	const struct DirectX::XMFLOAT4X4& projectionMatrix,
	class Shader* const shader 
)
{
	if (m_char == ' ')
		return;
	shader->SetShaderParameters(deviceContext,m_texture->GetTexture());
	shader->SetShaderParameters(deviceContext, world, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(deviceContext);
}

void LetterSpriteStruct::Update()
{

	
}

void _vectorcall LetterSpriteStruct::SetPosition(const DirectX::XMFLOAT3& position)
{
	m_position = position;
}

const char LetterSpriteStruct::GetLetter() const modern_except_state
{
	if(m_letter)
	return m_letter->GetLetter();
	return ' ';
}

const char LetterSprite::GetLetter() const modern_except_state
{
	return m_char;
}

void _vectorcall LetterSprite::SetMatrixIdentity(const DirectX::XMMATRIX identity) modern_except_state
{
	XMStoreFloat4x4(&s_world, identity);
}

LetterSpriteStruct::LetterSpriteStruct(class LetterSprite* const letter)
{
	if (letter == nullptr)
	{
		m_letter = nullptr;
		return;
	}
		m_letter = letter;
}

void LetterSpriteStruct::Render(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, Shader* const shader)
{
	if (m_letter)
	{
		DirectX::XMStoreFloat4x4(&s_world, XMMatrixTranslation(m_position.x, m_position.y, m_position.z));
		m_letter->Render(deviceContext, s_world,viewMatrix,projectionMatrix,shader);
	}
}

void LetterSpriteStruct::PreRender(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix, Shader* const shader)
{
	if (m_letter)
	{
		DirectX::XMStoreFloat4x4(&s_world, XMMatrixTranslation(m_position.x+3.f, m_position.y-3.f, m_position.z));
		m_letter->Render(deviceContext, s_world, viewMatrix, projectionMatrix, shader);
	}
}
