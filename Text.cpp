#include "Text.h"


namespace
{
	static ID3D11Device * m_device = nullptr;
	static ID3D11DeviceContext * m_deviceContext = nullptr;
	static Shader * m_shader = nullptr;
	static TextFont* m_font = nullptr;
}


Text::Text()
{
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

void Text::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader, TextFont* font)
{
	m_device = device;
	m_deviceContext = deviceContext;
	m_shader = shader;
	m_font = font;

	this->Initialize();

}

void Text::Render(
	struct ID3D11DeviceContext * const deviceContext,
	DirectX::XMFLOAT4X4& worldMatrix,
	DirectX::XMFLOAT4X4& viewMatrix,
	DirectX::XMFLOAT4X4& projectionMatrix
)
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
		sumup += ((m_font->GetWidthOfLetter('o'))*0.4f);
		else
		sumup += ((m_font->GetWidthOfLetter(letter->m_char))*0.4f);
	}
}

void Text::SetText(std::string text)
{
	
		//if (!m_letters.empty())
		//{
		//	for (auto && letter : m_letters)
		//	{
		//		if (letter)
		//		{
		//			delete letter;
		//			letter = nullptr;
		//		}
		//	}
		//}
		//m_letters.clear();
		m_text = text;

		//if (m_letters.size() < text.size())
		//	m_letters.expand_size(text.size());
		//else if (m_letters.size() > text.size())
		//	m_letters.shrink();

		//for (auto letter : text)
		//{
		//	LetterSpriteStruct* m_spriteStruct = new LetterSpriteStruct();
		//	m_spriteStruct->m_char = letter;
		//	m_letters.push_back(m_spriteStruct);
		//}
		//
		//this->Initialize();

		for (int32_t i = 0; i < m_letters.size() &&i < m_text.size(); i++)
		{
			m_letters.at(i)->m_char = text.at(i);
		}

		//this->Initialize();
}

void Text::SetText(const _bstr_t text)
{
	if (!m_letters.empty())
	{
		for (auto&& letter : m_letters)
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
	for (auto letter : m_text)
	{

		LetterSpriteStruct* m_spriteStruct = new LetterSpriteStruct();
		m_spriteStruct->m_char = letter;
		m_letters.push_back(m_spriteStruct);
	}

	//this->Initialize();

	//for (auto&& letter : m_letters)
	//{
	//	XMStoreFloat4x4(&(letter->m_world), XMMatrixIdentity());
	//	//letter->m_sprite = new LetterSprite(m_font, letter->m_char, 12.0f, m_shader);
	//	//letter->m_sprite->Initialize(m_device, m_deviceContext, m_shader, m_font);
	//}
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
		letter->m_sprite = new LetterSprite(m_font, letter->m_char, 12.0f, m_shader);
		letter->m_sprite->Initialize(m_device, m_deviceContext, m_shader, m_font);
	}
}
