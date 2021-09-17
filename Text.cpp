#include "Text.h"

namespace
{
	static ID3D11Device * m_device = nullptr;
	static ID3D11DeviceContext * m_deviceContext = nullptr;

	//static Shader * m_shader = nullptr;
	//static TextFont* m_font = nullptr;
}


Text::Text() : 
	m_letters(* new modern_array<struct LetterSpriteStruct*>()),
	m_spaceWidth(32.f),
	m_alignment(TextAlignment::TEXT_ALIGN_CENTER),
	m_position({0.f,0.f,0.f})
{
}

Text::Text(const TextAlignment align) :
	m_letters(*new modern_array<struct LetterSpriteStruct*>()),
	m_spaceWidth(32.f),
	m_alignment(align),
	m_position({ 0.f,0.f,0.f })
{
}


Text::~Text()
{
	//for (auto && letter : m_letters)
	//{
	//	if (letter)
	//	{
	//		delete letter;
	//		letter = nullptr;
	//	}
//}

	//DeleteAsyn

	class GarbageCollector* const collector = GarbageCollector::GetInstance();
	collector->AsyncDeleteArray(&m_letters);
}

void Text::Update()
{
	for (auto letter : m_letters)
	{
		letter->Update();
	}
}

void Text::Initialize(
	struct ID3D11Device* const device,
	struct ID3D11DeviceContext* const deviceContext,
	class Shader* const shader,
	class TextFont* const font,
	float size
)
{
	m_device = device;
	m_deviceContext = deviceContext;
	m_shader = shader;
	m_font = font;
	m_size = size;

	//this->Initialize();

}

void Text::Render(
	struct ID3D11DeviceContext * const deviceContext,
	const struct DirectX::XMFLOAT4X4& viewMatrix,
	const struct DirectX::XMFLOAT4X4& projectionMatrix,
	class Shader* const shader
)
{
	for (auto&& letter : m_letters)
	{
		letter->Render(deviceContext, viewMatrix, projectionMatrix,shader);
	}
}

void Text::SetPosition(XMFLOAT3 position)
{
	m_position = position;
	DirectX::XMFLOAT3 sumup = { 0.f,0.f,0.f };
	switch (m_alignment)
	{
	case TextAlignment::TEXT_ALIGN_LEFT:
	{
		for (auto&& letter : m_letters)
		{
			letter->SetPosition(modern_xfloat3_sum(position, sumup));
			if (letter->GetLetter() == ' ')
				sumup.x += m_spaceWidth * 0.48f;
			else
				sumup.x += ((m_font->GetWidthOfLetter(letter->GetLetter())) * 0.48f);
		}
		m_width = sumup.x;
		break;
	}
	case TextAlignment::TEXT_ALIGN_CENTER:
	{
		for (auto&& letter : m_letters)
		{
				sumup.x += ((m_font->GetWidthOfLetter(letter->GetLetter())) * 0.48f);
		}
		m_width = sumup.x;
		sumup.x = (m_width / -2.f);
		for (auto&& letter : m_letters)
		{
			letter->SetPosition(modern_xfloat3_sum(position, sumup));
			if (letter->GetLetter() == ' ')
				sumup.x += m_spaceWidth * 0.48f;
			else
				sumup.x += ((m_font->GetWidthOfLetter(letter->GetLetter())) * 0.48f);
		}
		break;
	}
	case TextAlignment::TEXT_ALIGN_RIGHT:
	{
		for (auto&& letter : m_letters)
		{
			sumup.x += ((m_font->GetWidthOfLetter(letter->GetLetter())) * 0.48f);
		}
		m_width = sumup.x;
		sumup.x = (m_width * -1.f);
		for (auto&& letter : m_letters)
		{
			letter->SetPosition(modern_xfloat3_sum(position, sumup));
			if (letter->GetLetter() == ' ')
				sumup.x += m_spaceWidth * 0.48f;
			else
				sumup.x += ((m_font->GetWidthOfLetter(letter->GetLetter())) * 0.48f);
		}
		break;
	}
	}

}

void Text::SetText(std::string text)
{

	//if (!m_letters.empty())
	//{
	//for (auto&& letter : m_letters)
	//{
	//	if (letter)
	//	{
	//		delete letter;
	//		letter = nullptr;
	//	}
	//}
//}

	m_text = text;

	bool updatePosition = false;

	if (m_letters.empty() == false)
	{
		// THIS IS SO FUCKING STUPID I CANT BELIEVE ITS MINE
		//class GarbageCollector* const collector = GarbageCollector::GetInstance();
		//collector->AsyncDeleteArray(&m_letters);
		//m_letters = (*new modern_array<struct LetterSpriteStruct*>());

		for (auto&& ele : m_letters)
		{
			delete ele;
			ele = nullptr;
		}
		m_letters.clear();
		m_letters.shrink();
		updatePosition = true;
	}

	//m_letters.clear();
		//m_letters.clear();
		

		//if (m_letters.size() < text.size())
		//	m_letters.expand_size(text.size());
		//else if (m_letters.size() > text.size())
		//	m_letters.shrink();

		for (int32_t i = 0;i < m_text.length();i++)
		{
			
			auto t = m_font->GetSprite(this, m_text[i]);
			if(t)
			m_letters.push_back(new LetterSpriteStruct(t));
			//m_letters[i]->m_sprite = m_font->GetSprite(this, text[i]);
		//	m_letters.push_back(m_spriteStruct);
		}
		//
		//this->Initialize();

		if (updatePosition)
			UpdatePosition();
		

		//for (int32_t i = 0; i < m_letters.size() &&i < m_text.size(); i++)
		//{
			//m_letters.at(i)->m_char = text.at(i);
			//m_letters[i] = m_font.G
		//}

		//this->Initialize();
}
/*
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

	///	class Text::LetterSpriteStruct* m_spriteStruct = new class Text::LetterSpriteStruct();
		//m_spriteStruct->m_char = letter;
		//m_letters.push_back(m_spriteStruct);
	}

	//this->Initialize();

	//for (auto&& letter : m_letters)
	//{
	//	XMStoreFloat4x4(&(letter->m_world), XMMatrixIdentity());
	//	//letter->m_sprite = new LetterSprite(m_font, letter->m_char, 12.0f, m_shader);
	//	//letter->m_sprite->Initialize(m_device, m_deviceContext, m_shader, m_font);
	//}
}
*/
string Text::GetText()
{
	return m_text;
}

float Text::GetSize() const noexcept
{
	return m_size;
}

Shader* const Text::GetShader()
{
	return m_shader;
}

void Text::Initialize()
{
	for (auto && letter : m_letters)
	{
		//XMStoreFloat4x4(&(letter), XMMatrixIdentity());
		//letter->m_sprite = new LetterSprite(m_font, letter->m_char, 12.0f, m_shader);
		//letter->m_sprite->Initialize(m_device, m_deviceContext, m_shader, m_font);
		///letter->m_sprite = m_font->GetSprite(letter->m_char);
	}
}

void Text::UpdatePosition()
{
	Text::SetPosition(m_position);
}
