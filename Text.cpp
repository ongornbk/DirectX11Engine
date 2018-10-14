#include "Text.h"


namespace
{
	static ID3D11Device * m_device = nullptr;
	static ID3D11DeviceContext * m_deviceContext = nullptr;
	static Shader * m_shader = nullptr;
	static Font * m_font = nullptr;
}


Text::Text()
{
	m_letters.reserve(10);
}


Text::~Text()
{
	for (auto && letter : m_letters)
	{
		if (letter->m_sprite)
		{
			delete letter->m_sprite;
			letter->m_sprite = NULL;
		}
}
}

void Text::Update()
{
	for (auto letter : m_letters)
	{
		letter->m_sprite->Update();
	}
}

void Text::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, Font * font)
{
	m_device = device;
	m_deviceContext = deviceContext;
	m_shader = shader;
	m_font = font;

	this->Initialize();

}

void Text::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	for (auto&& letter : m_letters)
	{
		letter->m_sprite->Render(deviceContext, letter->m_world, viewMatrix, projectionMatrix);
	}
}

void Text::SetPosition(XMFLOAT3 position)
{
	float sumup = 0.0f;
	for (auto && letter : m_letters)
	{
		XMStoreFloat4x4(&letter->m_world, XMMatrixTranslation((position.x+sumup),position.y,0.0f));
		if(letter->m_char==' ')
		sumup += ((m_font->GetWidthOfLetter('o'))*0.6f);
		else
		sumup += ((m_font->GetWidthOfLetter(letter->m_char))*0.6f);
	}
}

void Text::SetText(std::string text)
{
	
		if (!m_letters.empty())
		{
			for (auto && letter : m_letters)
			{
				if (letter)
				{
					delete letter;
					letter = nullptr;
				}
			}
		}
		m_letters.clear();
		m_text = text;
		for (auto letter : text)
		{
			LetterSpriteStruct* m_spriteStruct = new LetterSpriteStruct();
			m_spriteStruct->m_char = letter;
			m_letters.push_back(m_spriteStruct);
		}

		this->Initialize();
}

string Text::GetText()
{
	return string();
}

void Text::Initialize()
{
	for (auto && letter : m_letters)
	{
		XMStoreFloat4x4(&(letter->m_world), XMMatrixIdentity());
		letter->m_sprite = new LetterSprite(m_font, letter->m_char, 18.0f, m_shader);
		letter->m_sprite->Initialize(m_device, m_deviceContext, m_shader, m_font);
	}
}
