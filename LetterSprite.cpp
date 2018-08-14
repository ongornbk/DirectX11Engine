#include "LetterSprite.h"
#include "ResourceManager.h"
#include "Onion.h"


LetterSprite::LetterSprite(Font * font,char letter, float size,Shader* shader)
{

#pragma warning(disable : 4996)

	//ResourceManager::GetInstance()->PrintOutTextures();
	//Onion::Console::Println(font->GetName());

	this->m_shader = shader;
	this->m_vertexBuffer = NULL;
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

void LetterSprite::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader,Font* font)
{
	m_vertexBuffer = new VertexBuffer();
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->InitializePart(device, shader, sizexy,font->GetCoordsOfLetter(m_char), true);
}

void LetterSprite::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_shader->SetShaderParameters(deviceContext,m_texture->GetTexture());
	m_shader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(deviceContext);
}

void LetterSprite::Update()
{


}
